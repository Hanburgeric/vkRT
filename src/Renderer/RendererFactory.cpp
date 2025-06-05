#include "RendererFactory.h"

// src
#include "VulkanRenderer.h"
#include "OpenGlRenderer.h"

namespace vkrt::renderer {

std::unique_ptr<Renderer> Factory::Create(Type type) {
  switch (type) {
    case Type::Vulkan: { return CreateVulkan(); }
    case Type::OpenGL: { return CreateOpenGl(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Renderer> Factory::CreateVulkan() {
  return std::make_unique<VulkanRenderer>();
}

std::unique_ptr<Renderer> Factory::CreateOpenGl() {
  return std::make_unique<OpenGlRenderer>();
}

}  // namespace vkrt::renderer