#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// src
#include "Renderer.h"

namespace vkrt {
namespace renderer {

class OpenGlRenderer : public Renderer {
public:
  bool Initialize() override;
  void Shutdown() override;
};

} // namespace renderer
} // namespace vkrt

#endif // OPENGLRENDERER_H
