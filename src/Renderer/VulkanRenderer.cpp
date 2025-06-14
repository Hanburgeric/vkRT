#include "VulkanRenderer.h"

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

VulkanRenderer::~VulkanRenderer() {
  VulkanRenderer::Shutdown();
}

bool VulkanRenderer::Initialize() {
  return false;
}

void VulkanRenderer::Shutdown() {
}

} // namespace renderer
} // namespace vkrt
