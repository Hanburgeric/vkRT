#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class VulkanRenderer : public Renderer {
public:
  constexpr Type type() const override { return Type::Vulkan; }

  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // VULKANRENDERER_H
