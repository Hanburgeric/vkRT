#include "Application.h"

// STL
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

// spdlog
#include "spdlog/spdlog.h"

// SDL
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"

// vulkan
#include "vulkan/vulkan_raii.hpp"

namespace vkrt {

Application::~Application() {
  Shutdown();
}

bool Application::Initialize() {
  if (!InitializePlatform()) {
    spdlog::error("Failed to initialize application platform.");
    return false;
  }

  if (!InitializeRenderer()) {
    spdlog::error("Failed to initialize application renderer.");
    return false;
  }

  return true;
}

void Application::Run() {
  // Main loop
  while (!should_quit_) {
    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: { should_quit_ = true; break; }
        default: { break; }
      }
    }

    // Update physics

    // Render

  }
}

void Application::Shutdown() {
  ShutdownRenderer();
  ShutdownPlatform();
}

bool Application::InitializePlatform() {
  // Initialize SDL3
  constexpr SDL_InitFlags init_flags{
    SDL_INIT_VIDEO | SDL_INIT_GAMEPAD
  };
  platform_initialized_ = SDL_Init(init_flags);
  if (!platform_initialized_) {
    spdlog::error(SDL_GetError());
    spdlog::error("Failed to initialize SDL3.");
    return false;
  } else {
    spdlog::info("SDL3 initialized.");
  }

  // Create window
  constexpr SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
    | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN
  };
  window_ = std::unique_ptr<SDL_Window,
                            decltype(&SDL_DestroyWindow)>{
    SDL_CreateWindow("vkRT Application", 640, 480, window_flags),
    SDL_DestroyWindow
  };
  if (!window_) {
    spdlog::error(SDL_GetError());
    spdlog::error("Failed to create SDL3 window.");
    return false;
  } else {
    spdlog::info("SDL3 window created.");
  }

  return true;
}

bool Application::InitializeRenderer() {
  // Create Vulkan instance
  if (!CreateVulkanInstance()) {
    spdlog::error("Failed to create Vulkan instance.");
    return false;
  } else {
    spdlog::info("Vulkan instance created.");
  }

  // Create Vulkan debug messenger
  if (!CreateVulkanDebugMessenger()) {
    spdlog::error("Failed to create Vulkan debug messenger.");
    return false;
  } else {
    spdlog::info("Vulkan debug messenger created.");
  }

  return true;
}

bool Application::CreateVulkanInstance() {
  // Create (temporary) debug messenger info
  constexpr vk::DebugUtilsMessengerCreateInfoEXT debug_messenger_info{
    .pNext{},
    .flags{},
    .messageSeverity{ vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError },
    .messageType{ vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                  | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                  | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance },
    .pfnUserCallback{ VulkanDebugMessageCallback },
    .pUserData{}
  };

  // Create application info
  constexpr vk::ApplicationInfo application_info{
    .pNext{},
    .pApplicationName{ "vkRT Application" },
    .applicationVersion{ VK_MAKE_API_VERSION(0, 1, 0, 0) },
    .pEngineName{ "vkRT" },
    .engineVersion{ VK_MAKE_API_VERSION(0, 1, 0, 0) },
    .apiVersion{ VK_MAKE_API_VERSION(0, 1, 3, 0) }
  };

  // Add layers required by the application
  std::vector<const char*> required_layers{};
  required_layers.emplace_back("VK_LAYER_KHRONOS_validation");

  // If any layers are required, check whether they are available
  if (!required_layers.empty()) {
    spdlog::info("Required Vulkan instance layers:");
    for (const char* layer : required_layers) {
      spdlog::info("  {}", layer);
    }

    // Query layers supported by this installation of Vulkan
    const std::vector<vk::LayerProperties> supported_layers{
      vk_context_.enumerateInstanceLayerProperties()
    };

    spdlog::info("Supported Vulkan instance layers:");
    for (const vk::LayerProperties& layer : supported_layers) {
      spdlog::info("  {}", layer.layerName.data());
    }

    // Check for any missing layers,
    // using an unordered set for constant lookup times
    std::unordered_set<std::string> supported_layer_set{};
    supported_layer_set.reserve(supported_layers.size());
    for (const vk::LayerProperties& layer : supported_layers) {
      supported_layer_set.emplace(layer.layerName.data());
    }

    std::vector<std::string> missing_layers{};
    for (const char* layer : required_layers) {
      if (!supported_layer_set.contains(layer)) {
        missing_layers.emplace_back(layer);
      }
    }

    // Report any missing layers and return failure
    if (!missing_layers.empty()) {
      spdlog::info("Missing Vulkan instance layers:");
      for (const std::string& layer : missing_layers) {
        spdlog::warn("  {}", layer);
      }
      return false;
    }
  }

  // Add extensions required by the application
  std::vector<const char*> required_extensions{};
  required_extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  // Query extensions required by SDL3
  uint32_t required_extension_count{};
  char const* const* required_extension_names{
    SDL_Vulkan_GetInstanceExtensions(&required_extension_count)
  };

  // Add extensions required by SDL3
  required_extensions.reserve(
    required_extensions.size() + required_extension_count
  );
  for (uint32_t i{ 0U }; i < required_extension_count; ++i) {
    required_extensions.emplace_back(required_extension_names[i]);
  }

  // If any extensions are required, check whether they are available
  if (!required_extensions.empty()) {
    spdlog::info("Required Vulkan instance extensions:");
    for (const char* extension : required_extensions) {
      spdlog::info("  {}", extension);
    }

    // Query extensions supported by this installation of Vulkan
    const std::vector<vk::ExtensionProperties> supported_extensions{
      vk_context_.enumerateInstanceExtensionProperties()
    };

    spdlog::info("Supported Vulkan instance extensions:");
    for (const vk::ExtensionProperties& extension : supported_extensions) {
      spdlog::info("  {}", extension.extensionName.data());
    }

    // Check for any missing extensions,
    // using an unordered set for constant lookup times
    std::unordered_set<std::string> supported_extension_set{};
    supported_extension_set.reserve(supported_extensions.size());
    for (const vk::ExtensionProperties& extension : supported_extensions) {
      supported_extension_set.emplace(extension.extensionName.data());
    }

    std::vector<std::string> missing_extensions{};
    for (const char* extension : required_extensions) {
      if (!supported_extension_set.contains(extension)) {
        missing_extensions.emplace_back(extension);
      }
    }

    // Report any missing extensions and return failure
    if (!missing_extensions.empty()) {
      spdlog::info("Missing Vulkan instance extensions:");
      for (const std::string& extension : missing_extensions) {
        spdlog::warn("  {}", extension);
      }
      return false;
    }
  }

  // Create instance info
  const vk::InstanceCreateInfo instance_create_info{
    .pNext{ &debug_messenger_info },
    .pApplicationInfo{ &application_info },
    .enabledLayerCount{ static_cast<uint32_t>(required_layers.size()) },
    .ppEnabledLayerNames{ required_layers.data() },
    .enabledExtensionCount{ static_cast<uint32_t>(required_extensions.size()) },
    .ppEnabledExtensionNames{ required_extensions.data() }
  };

  // Attempt to create instance and return result
  try {
    vk_instance_ = vk_context_.createInstance(instance_create_info);
    return true;
  } catch (const vk::SystemError& e) {
    spdlog::error(e.what());
    return false;
  }
}

bool Application::CreateVulkanDebugMessenger() {
  // Create debug messenger info
  constexpr vk::DebugUtilsMessengerCreateInfoEXT debug_messenger_info{
    .pNext{},
    .flags{},
    .messageSeverity{ vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError },
    .messageType{ vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                  | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                  | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance },
    .pfnUserCallback{ VulkanDebugMessageCallback },
    .pUserData{}
  };

  // Attempt to create debug messenger and return result
  try {
    vk_debug_messenger_ =
      vk_instance_.createDebugUtilsMessengerEXT(debug_messenger_info);
    return true;
  } catch (const vk::SystemError& e) {
    spdlog::error(e.what());
    return false;
  }
}

VKAPI_ATTR VkBool32 VKAPI_CALL Application::VulkanDebugMessageCallback(
  vk::DebugUtilsMessageSeverityFlagBitsEXT message_severity,
  vk::DebugUtilsMessageTypeFlagsEXT message_type,
  const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
  void* user_data
) {
  switch (message_severity) {
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose: {
      spdlog::debug(callback_data->pMessage);
      break;
    }
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo: {
      spdlog::info(callback_data->pMessage);
      break;
    }
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning: {
      spdlog::warn(callback_data->pMessage);
      break;
    }
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError: {
      spdlog::error(callback_data->pMessage);
      break;
    }
    default: {
      spdlog::trace("[unknown] {}", callback_data->pMessage);
      break;
    }
  }

  spdlog::info(callback_data->pMessage);

  return VK_FALSE;
}

void Application::ShutdownRenderer() {
  // Destroy debug messenger
  vk_debug_messenger_.clear();
  spdlog::info("Vulkan debug messenger destroyed.");

  // Destroy instance
  vk_instance_.clear();
  spdlog::info("Vulkan instance destroyed.");
}

void Application::ShutdownPlatform() {
  // Destroy window
  if (window_) {
    window_.reset();
    spdlog::info("SDL3 window destroyed.");
  }

  // Shutdown platform
  if (platform_initialized_) {
    SDL_Quit();
    platform_initialized_ = false;
    spdlog::info("SDL3 shut down.");
  }
}

} // namespace vkrt
