#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// src
#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"

// Forward declarations
namespace vkrt::platform{ class Platform; }
namespace vkrt::renderer{ class Renderer; }
struct ImGuiContext;

namespace vkrt {

class Application {
public:
  Application();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  bool InitializePlatform();
  bool InitializeRenderer();
  bool InitializeImGui();

  void ShutdownPlatform();
  void ShutdownRenderer();
  void ShutdownImGui();

private:
  platform::Type platform_type_;
  std::unique_ptr<platform::Platform> platform_;

  renderer::Type renderer_type_;
  std::unique_ptr<renderer::Renderer> renderer_;
};

}  // namespace vkrt

#endif // APPLICATION_H
