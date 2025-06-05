#include "GlfwPlatform.h"

// ImGui
#include "imgui_impl_glfw.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

Type GlfwPlatform::type() const {
  return Type::GLFW;
}

bool GlfwPlatform::InitializeImGui() const {
  return true;
}

void GlfwPlatform::BeginNewImGuiFrame() const {
  ImGui_ImplGlfw_NewFrame();
}

void GlfwPlatform::ShutdownImGui() const {
  ImGui_ImplGlfw_Shutdown();
}

} // namespace platform
} // namespace vkrt
