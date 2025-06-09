#include "RendererFactory.h"

// STL
#include <memory>

// src
#include "Renderer.h"
#include "RendererTypes.h"
#include "VulkanRenderer.h"
#include "OpenGlRenderer.h"

namespace vkrt {
namespace renderer {

std::unique_ptr<Renderer> Factory::CreateRenderer(Type type) {
  switch (type) {
    case Type::Vulkan: { return CreateVulkanRenderer(); }
    case Type::OpenGL: { return CreateOpenGlRenderer(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Renderer> Factory::CreateVulkanRenderer() {
  return std::make_unique<VulkanRenderer>();
}

std::unique_ptr<Renderer> Factory::CreateOpenGlRenderer() {
  return std::make_unique<OpenGlRenderer>();
}

} // namespace renderer
} // namespace vkrt
