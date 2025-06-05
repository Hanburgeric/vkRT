#include "VulkanRenderer.h"

// ImGui
#include "imgui_impl_vulkan.h"

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

Type VulkanRenderer::type() const {
  return Type::Vulkan;
}

bool VulkanRenderer::InitializeImGui() const {
  // ???
  return true;
}

void VulkanRenderer::BeginNewImGuiFrame() const {
  ImGui_ImplVulkan_NewFrame();
}

void VulkanRenderer::RenderImGuiDrawData(ImDrawData* draw_data) const {
  // ???
}

void VulkanRenderer::ShutdownImGui() const {
  ImGui_ImplVulkan_Shutdown();
}

} // namespace renderer
} // namespace vkrt
