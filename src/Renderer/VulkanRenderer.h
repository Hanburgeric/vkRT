#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

// Vulkan
#include <vulkan/vulkan.h>

// STL
#include <vector>

// ImGui
#include "imgui_impl_vulkan.h"

// src
#include "Renderer.h"

namespace vkrt::renderer {

class VulkanRenderer : public Renderer {
public:
  VulkanRenderer();
  ~VulkanRenderer() override;

  bool Initialize(const RendererCreateInfo& info) override;
  void Shutdown() override;

  void NewFrame() override;
  void RenderFrame(ImDrawData* draw_data) override;
  void Present() override;

  void OnResize(int width, int height) override;
  void SetClearColor(float r, float g, float b, float a) override;

  // ImGui integration
  bool InitializeImGui() override;
  void ShutdownImGui() override;

private:
  bool SetupVulkan();
  bool SetupVulkanWindow(int width, int height);
  void CleanupVulkan();
  void CleanupVulkanWindow();
  void FrameRender(ImDrawData* draw_data);
  void FramePresent();

  static void CheckVkResult(VkResult err);

private:
  platform::Platform* platform_;

  // Vulkan objects
  VkAllocationCallbacks* allocator_;
  VkInstance instance_;
  VkPhysicalDevice physical_device_;
  VkDevice device_;
  uint32_t queue_family_;
  VkQueue queue_;
  VkPipelineCache pipeline_cache_;
  VkDescriptorPool descriptor_pool_;

  // Window data
  ImGui_ImplVulkanH_Window main_window_data_;
  uint32_t min_image_count_;
  bool swap_chain_rebuild_;

  // Clear color
  VkClearValue clear_value_;

  int width_, height_;
};

}  // namespace vkrt::renderer

#endif // VULKANRENDERER_H