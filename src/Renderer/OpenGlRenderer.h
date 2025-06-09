#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class OpenGlRenderer : public Renderer {
public:
  constexpr Type type() const override { return Type::OpenGL; }

  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // OPENGLRENDERER_H
