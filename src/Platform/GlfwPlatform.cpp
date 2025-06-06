#include "GlfwPlatform.h"

// GLFW
#include "GLFW/glfw3.h"

// ImGui
#include "imgui_impl_glfw.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {
namespace platform {

Type GlfwPlatform::type() const {
  return Type::GLFW;
}

bool GlfwPlatform::Initialize(vkrt::renderer::Type renderer_type) {
  return true;
}

bool GlfwPlatform::ShouldQuit() const {
  return glfwWindowShouldClose(window_);
}

void GlfwPlatform::HandleEvents() {
  glfwPollEvents();
}

void GlfwPlatform::Shutdown() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

bool GlfwPlatform::InitializeImGui(vkrt::renderer::Type renderer_type) const {
  switch (renderer_type) {
    case renderer::Type::Vulkan: {
      return ImGui_ImplGlfw_InitForVulkan(window_, true);
    }
    case renderer::Type::OpenGL: {
      return ImGui_ImplGlfw_InitForOpenGL(window_, true);
    }
    default: {
      return false;
    }
  }
}

void GlfwPlatform::BeginNewImGuiFrame() const {
  ImGui_ImplGlfw_NewFrame();
}

void GlfwPlatform::ShutdownImGui() const {
  ImGui_ImplGlfw_Shutdown();
}

} // namespace platform
} // namespace vkrt
