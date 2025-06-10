#include "OpenGlRenderer.h"

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

OpenGlRenderer::~OpenGlRenderer() {
  OpenGlRenderer::Shutdown();
}

bool OpenGlRenderer::Initialize() {
  return true;
}

void OpenGlRenderer::Shutdown() {
}

} // namespace renderer
} // namespace vkrt
