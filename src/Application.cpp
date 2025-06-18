#include "Application.h"

// STL
#include <memory>

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
    return false;
  }

  if (!InitializeRenderer()) {
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
  // Initialize platform
  constexpr SDL_InitFlags init_flags{
    SDL_INIT_VIDEO | SDL_INIT_GAMEPAD
  };
  platform_initialized_ = SDL_Init(init_flags);
  if (!platform_initialized_) {
    spdlog::error(SDL_GetError());
    spdlog::error("Application failed to initialize platform.");
    return false;
  } else {
    spdlog::info("Application platform initialized.");
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
    spdlog::error("Application failed to create window.");
    return false;
  } else {
    spdlog::info("Application window created.");
  }

  return true;
}

bool Application::InitializeRenderer() {
  if (!CreateRendererInstance()) {
    spdlog::error("Application failed to create renderer instance.");
    return false;;
  } else {
    spdlog::info("Application renderer instance created.");
  }

  return true;
}

bool Application::CreateRendererInstance() {
  // Create application info
  VkApplicationInfo application_info{};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  // application_info.pNext;
  application_info.pApplicationName = "vkRT Application";
  application_info.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  application_info.pEngineName = "vkRT";
  application_info.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  application_info.apiVersion = VK_API_VERSION_1_4;

  // Query extensions required by the platform needed to create instance info
  uint32_t extension_count{};
  char const* const* extension_names {
    SDL_Vulkan_GetInstanceExtensions(&extension_count)
  };

  VkInstanceCreateInfo instance_create_info{};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  // instance_create_info.pNext;
  // instance_create_info.flags;
  instance_create_info.pApplicationInfo = &application_info;
  // instance_create_info.enabledLayerCount;
  // instance_create_info.ppEnabledLayerNames;
  instance_create_info.enabledExtensionCount = extension_count;
  instance_create_info.ppEnabledExtensionNames = extension_names;

  VkResult result{
    vkCreateInstance(&instance_create_info, nullptr, &renderer_instance_)
  };

  return result == VK_SUCCESS;
}

void Application::ShutdownRenderer() {
  if (renderer_instance_) {
    vkDestroyInstance(renderer_instance_, nullptr);
    spdlog::info("Application renderer instance destroyed.");
  }
}

void Application::ShutdownPlatform() {
  // Destroy window
  if (window_) {
    window_.reset();
    spdlog::info("Application window destroyed.");
  }

  // Shutdown platform
  if (platform_initialized_) {
    SDL_Quit();
    platform_initialized_ = false;
    spdlog::info("Application platform shut down.");
  }
}

} // namespace vkrt
