#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  constexpr Type type() const override { return Type::GLFW; }

  bool Initialize(const renderer::Renderer& renderer) override;
  void Shutdown() override;

private:
  bool InitializeForVulkan(const renderer::Renderer& renderer);
  bool InitializeForOpenGl(const renderer::Renderer& renderer);
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
