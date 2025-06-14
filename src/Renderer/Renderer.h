#ifndef RENDERER_H
#define RENDERER_H

// src
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class Renderer {
public:
  virtual ~Renderer() = default;

  virtual constexpr Type type() const = 0;

  virtual bool Initialize() = 0;
  virtual void Shutdown() = 0;
};

} // namespace renderer
} // namespace vkrt

#endif // RENDERER_H
