#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// Forward declarations
namespace vkrt::renderer{ class Renderer; }
namespace vkrt::platform{ class Platform; }
struct ImGuiContext;

namespace vkrt {

class Application {
public:
  Application();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  std::unique_ptr<renderer::Renderer> renderer_;
  std::unique_ptr<platform::Platform> platform_;
  ImGuiContext* imgui_context_;
};

} // namespace vkrt

#endif // APPLICATION_H
