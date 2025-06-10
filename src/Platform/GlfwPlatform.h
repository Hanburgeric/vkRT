#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// STL
#include <string>

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  constexpr Type type() const override { return Type::GLFW; }

  bool Initialize(const renderer::Renderer& renderer,
                  const std::string& window_title,
                  int window_width, int window_height) override;
  bool ShouldQuit() const override;
  void HandleEvents() override;
  void Shutdown() override;

private:
  bool InitializeForVulkan(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);
  bool InitializeForOpenGl(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
