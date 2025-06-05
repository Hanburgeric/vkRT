#ifndef RENDERER_H
#define RENDERER_H

// src
#include "RendererTypes.h"

// Forward declarations
struct ImDrawData;

namespace vkrt {
namespace renderer {

class Renderer {
public:
  virtual ~Renderer() = default;

  virtual Type type() const = 0;

  virtual bool InitializeImGui() const = 0;
  virtual void BeginNewImGuiFrame() const = 0;
  virtual void RenderImGuiDrawData(ImDrawData* draw_data) const = 0;
  virtual void ShutdownImGui() const = 0;
};

} // namespace renderer
} // namespace vkrt

#endif // RENDERER_H
