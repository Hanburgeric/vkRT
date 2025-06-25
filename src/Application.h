#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// SDL
#include "SDL3/SDL.h"

// vulkan
#include "vulkan/vulkan_raii.hpp"

namespace vkrt {

class Application {
public:
  Application() = default;
  ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  bool Initialize();
  void Run();
  void Shutdown();

private:
  bool InitializePlatform();

  bool InitializeRenderer();
  bool CreateVulkanInstance();
  bool CreateVulkanDebugMessenger();
  static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugMessageCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT message_severity,
    vk::DebugUtilsMessageTypeFlagsEXT message_type,
    const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
  );

  void ShutdownRenderer();
  void ShutdownPlatform();

private:
  bool platform_initialized_{ false };
  std::unique_ptr<SDL_Window,
                  decltype(&SDL_DestroyWindow)> window_{ nullptr, nullptr };
  bool should_quit_{ false };

  vk::raii::Context vk_context_{};
  vk::raii::Instance vk_instance_{ nullptr };
  vk::raii::DebugUtilsMessengerEXT vk_debug_messenger_{ nullptr };
};

} // namespace vkrt

#endif // APPLICATION_H
