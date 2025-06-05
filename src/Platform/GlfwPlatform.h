#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// GLFW
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// src
#include "Platform.h"

namespace vkrt::platform {

class GlfwPlatform : public Platform {
public:
  GlfwPlatform();
  ~GlfwPlatform() override;

  bool Initialize(const PlatformCreateInfo& info) override;
  void Shutdown() override;

  bool ShouldClose() const override;
  void PollEvents() override;
  void SwapBuffers() override;

  WindowInfo GetWindowInfo() const override;
  void GetFramebufferSize(int& width, int& height) const override;

  // ImGui integration
  bool InitializeImGui() override;
  void ShutdownImGui() override;
  void NewFrame() override;
  bool ProcessEvent(void* event) override;

  // Renderer-specific functionality
  void* GetRequiredInstanceExtensions(uint32_t& count) override;
  bool CreateSurface(void* instance, void* allocator, void* surface) override;
  void MakeContextCurrent() override;

private:
  static void ErrorCallback(int error, const char* description);

  GLFWwindow* window_;
  renderer::Type renderer_type_;
  int width_, height_;
};

}  // namespace vkrt::platform

#endif // GLFWPLATFORM_H