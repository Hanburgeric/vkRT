#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// SDL
#include "SDL3/SDL.h"

// vulkan
#include "vulkan/vulkan.h"

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
  bool EnableRendererValidation();

  void ShutdownRenderer();
  void ShutdownPlatform();

private:
  bool platform_initialized_{ false };
  std::unique_ptr<SDL_Window,
                  decltype(&SDL_DestroyWindow)> window_{ nullptr, nullptr };
  bool should_quit_{ false };

  VkInstance renderer_instance_{ nullptr };
};

} // namespace vkrt

#endif // APPLICATION_H
