#ifndef RENDERER_H
#define RENDERER_H

// STL
#include <memory>

// ImGui
#include "imgui.h"

// Forward declarations
namespace vkrt::platform { class Platform; }

namespace vkrt::renderer {

struct RendererCreateInfo {
  platform::Platform* platform = nullptr;
  int width = 1280;
  int height = 720;
};

class Renderer {
public:
  virtual ~Renderer() = default;

  virtual bool Initialize(const RendererCreateInfo& info) = 0;
  virtual void Shutdown() = 0;

  virtual void NewFrame() = 0;
  virtual void RenderFrame(ImDrawData* draw_data) = 0;
  virtual void Present() = 0;

  virtual void OnResize(int width, int height) = 0;
  virtual void SetClearColor(float r, float g, float b, float a) = 0;

  // ImGui integration
  virtual bool InitializeImGui() = 0;
  virtual void ShutdownImGui() = 0;
};

}  // namespace vkrt::renderer

#endif // RENDERER_H