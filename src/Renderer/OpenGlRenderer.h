#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// src
#include "Renderer.h"
#include "RendererTypes.h"

// Forward declarations
struct ImDrawData;

namespace vkrt {
namespace renderer {

class OpenGlRenderer : public Renderer {
public:
  Type type() const override;

  bool Initialize() override;
  void Shutdown() override;

  bool InitializeImGui() const override;
  void BeginNewImGuiFrame() const override;
  void RenderImGuiDrawData(ImDrawData* draw_data) const override;
  void ShutdownImGui() const override;
};

} // namespace renderer
} // namespace vkrt

#endif // OPENGLRENDERER_H
