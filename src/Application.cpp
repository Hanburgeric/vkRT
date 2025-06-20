#include "Application.h"

// STL
#include <memory>
#include <string>
#include <unordered_set>

// spdlog
#include "spdlog/spdlog.h"

// SDL
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"

// vulkan
#include "vulkan/vulkan.h"

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
  if (!CreateVulkanInstance()) {
    spdlog::error("Failed to create Vulkan instance.");
    return false;;
  } else {
    spdlog::info("Vulkan instance created.");
  }

  return true;
}

bool Application::CreateVulkanInstance() {
  // Create application info
  VkApplicationInfo application_info{};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  // application_info.pNext;
  application_info.pApplicationName = "vkRT Application";
  application_info.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  application_info.pEngineName = "vkRT";
  application_info.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  application_info.apiVersion = VK_API_VERSION_1_4;

  // Query extensions supported by this installation of Vulkan
  uint32_t supported_extension_count{};
  vkEnumerateInstanceExtensionProperties(
    nullptr, &supported_extension_count, nullptr
  );

  std::vector<VkExtensionProperties> supported_extensions{
    supported_extension_count
  };
  vkEnumerateInstanceExtensionProperties(
    nullptr, &supported_extension_count, supported_extensions.data()
  );

  spdlog::info("Supported Vulkan instance extensions:");
  for (const VkExtensionProperties& extension : supported_extensions) {
    spdlog::info("  {}", extension.extensionName);
  }

  // Query extensions required by SDL3 needed to create instance info
  uint32_t required_extension_count{};
  char const* const* required_extension_names{
      SDL_Vulkan_GetInstanceExtensions(&required_extension_count)
  };

  std::vector<const char*> required_extensions{};
  required_extensions.reserve(required_extension_count);
  for (uint32_t i{ 0U }; i < required_extension_count; ++i) {
    required_extensions.emplace_back(required_extension_names[i]);
  }

  // Add additional extensions required by the application
  // ???

  spdlog::info("Required Vulkan instance extensions:");
  for (const char* extension : required_extensions) {
    spdlog::info("  {}", extension);
  }

  // Check that all required extensions are supported,
  // using an unordered set for constant lookup times
  std::unordered_set<std::string> supported_extension_set{};
  for (const VkExtensionProperties& extension : supported_extensions) {
    supported_extension_set.emplace(extension.extensionName);
  }

  std::vector<std::string> missing_extensions{};
  for (const char* extension : required_extensions) {
    if (!supported_extension_set.contains(extension)) {
      missing_extensions.emplace_back(extension);
    }
  }

  if (!missing_extensions.empty()) {
    spdlog::info("Missing Vulkan instance extensions:");
    for (const std::string& extension : missing_extensions) {
      spdlog::error("  {}", extension);
    }

    return false;
  }

  // Create instance info
  VkInstanceCreateInfo instance_create_info{};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  // instance_create_info.pNext;
  // instance_create_info.flags;
  instance_create_info.pApplicationInfo = &application_info;
  // instance_create_info.enabledLayerCount;
  // instance_create_info.ppEnabledLayerNames;
  instance_create_info.enabledExtensionCount
    = static_cast<uint32_t>(required_extensions.size());
  instance_create_info.ppEnabledExtensionNames
    = required_extensions.data();

  VkResult result{
      vkCreateInstance(&instance_create_info, nullptr, &renderer_instance_)
  };

  return result == VK_SUCCESS;
}

bool Application::EnableRendererValidation() {
  const std::vector<std::string> validation_layers{
    "VK_LAYER_KHRONOS_validation"
  };
}

void Application::ShutdownRenderer() {
  if (renderer_instance_) {
    vkDestroyInstance(renderer_instance_, nullptr);
    spdlog::info("Vulkan instance destroyed.");
  }
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
