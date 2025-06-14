#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>
#include <string>

// src
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"

#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"

namespace vkrt {

class Application {
public:
  Application();

  bool Initialize(renderer::Type renderer_type,
                  platform::Type platform_type,
                  const std::string& window_title,
                  int window_width, int window_height);
  void Run();
  void Shutdown();

private:
  std::unique_ptr<renderer::Renderer> renderer_;
  std::unique_ptr<platform::Platform> platform_;
};

} // namespace vkrt

#endif // APPLICATION_H
