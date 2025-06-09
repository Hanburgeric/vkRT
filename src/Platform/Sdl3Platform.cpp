#include "Sdl3Platform.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/VulkanRenderer.h"
#include "../Renderer/OpenGlRenderer.h"

namespace vkrt {
namespace platform {

bool Sdl3Platform::Initialize(const renderer::Renderer& renderer) {
  switch (renderer.type()) {
    case renderer::Type::Vulkan: { return InitializeForVulkan(renderer); }
    case renderer::Type::OpenGL: { return InitializeForOpenGl(renderer); }
    default: { return false; }
  }
}

void Sdl3Platform::Shutdown() {
}

bool Sdl3Platform::InitializeForVulkan(const renderer::Renderer& renderer) {
  return false;
}

bool Sdl3Platform::InitializeForOpenGl(const renderer::Renderer& renderer) {
  return true;
}

} // namespace platform
} // namespace vkrt
