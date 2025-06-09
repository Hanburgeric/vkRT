#include "GlfwPlatform.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/VulkanRenderer.h"
#include "../Renderer/OpenGlRenderer.h"

namespace vkrt {
namespace platform {

bool GlfwPlatform::Initialize(const renderer::Renderer& renderer) {
  switch (renderer.type()) {
    case renderer::Type::Vulkan: { return InitializeForVulkan(renderer); }
    case renderer::Type::OpenGL: { return InitializeForOpenGl(renderer); }
    default: { return false; }
  }
}

void GlfwPlatform::Shutdown() {
}

bool GlfwPlatform::InitializeForVulkan(const renderer::Renderer& renderer) {
  return false;
}

bool GlfwPlatform::InitializeForOpenGl(const renderer::Renderer& renderer) {
  return true;
}

} // namespace platform
} // namespace vkrt
