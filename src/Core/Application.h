#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// ImGui
#include "imgui.h"

// src
#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {

struct ApplicationConfig {
  platform::Type platform_type = platform::Type::SDL3;
  renderer::Type renderer_type = renderer::Type::Vulkan;
  const char* window_title = "vkRT Application";
  int window_width = 1280;
  int window_height = 720;
};

class Application {
public:
  Application(const ApplicationConfig& config = {});
  ~Application();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  bool InitializePlatform();
  bool InitializeRenderer();
  bool InitializeImGui();

  void ShutdownImGui();
  void ShutdownRenderer();
  void ShutdownPlatform();

  void MainLoop();
  void HandleEvents();
  void RenderFrame();
  void RenderImGui();

private:
  ApplicationConfig config_;

  std::unique_ptr<platform::Platform> platform_;
  std::unique_ptr<renderer::Renderer> renderer_;

  bool running_;
  bool show_demo_window_;
  bool show_another_window_;
  ImVec4 clear_color_;
};

}  // namespace vkrt

#endif // APPLICATION_H