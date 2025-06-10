#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class VulkanRenderer : public Renderer {
public:
  VulkanRenderer() = default;
  ~VulkanRenderer() override;

  VulkanRenderer(const VulkanRenderer&) = delete;
  VulkanRenderer& operator=(const VulkanRenderer&) = delete;

  VulkanRenderer(VulkanRenderer&&) = delete;
  VulkanRenderer& operator=(VulkanRenderer&&) = delete;

  constexpr Type type() const override { return Type::Vulkan; }

  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // VULKANRENDERER_H
