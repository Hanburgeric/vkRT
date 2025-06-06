#ifndef APPLICATION_H
#define APPLICATION_H

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
  renderer::Renderer* renderer_;
  platform::Platform* platform_;
  ImGuiContext* imgui_context_;
};

} // namespace vkrt

#endif // APPLICATION_H
