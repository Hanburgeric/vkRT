#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

// src
#include "Renderer.h"

namespace vkrt {
namespace renderer {

class VulkanRenderer : public Renderer {
public:
  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // VULKANRENDERER_H
