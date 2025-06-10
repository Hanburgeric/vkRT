#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class OpenGlRenderer : public Renderer {
public:
  OpenGlRenderer() = default;
  ~OpenGlRenderer() override;

  OpenGlRenderer(const OpenGlRenderer&) = delete;
  OpenGlRenderer& operator=(const OpenGlRenderer&) = delete;

  OpenGlRenderer(OpenGlRenderer&&) = delete;
  OpenGlRenderer& operator=(OpenGlRenderer&&) = delete;

  constexpr Type type() const override { return Type::OpenGL; }

  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // OPENGLRENDERER_H
