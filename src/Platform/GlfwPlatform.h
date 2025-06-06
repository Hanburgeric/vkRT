#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// GLFW
#include "GLFW/glfw3.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  Type type() const override;

  bool Initialize(vkrt::renderer::Type renderer_type) override;
  bool ShouldQuit() const override;
  void HandleEvents() override;
  void Shutdown() override;

  bool InitializeImGui(vkrt::renderer::Type renderer_type) const override;
  void BeginNewImGuiFrame() const override;
  void ShutdownImGui() const override;

private:
  GLFWwindow* window_;
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
