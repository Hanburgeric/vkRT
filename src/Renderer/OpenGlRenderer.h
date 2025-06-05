#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// OpenGL
#if defined(_WIN32)
#include <windows.h>
#endif
#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

// src
#include "Renderer.h"

namespace vkrt::renderer {

class OpenGlRenderer : public Renderer {
public:
  OpenGlRenderer();
  ~OpenGlRenderer() override;

  bool Initialize(const RendererCreateInfo& info) override;
  void Shutdown() override;

  void NewFrame() override;
  void RenderFrame(ImDrawData* draw_data) override;
  void Present() override;

  void OnResize(int width, int height) override;
  void SetClearColor(float r, float g, float b, float a) override;

  // ImGui integration
  bool InitializeImGui() override;
  void ShutdownImGui() override;

private:
  platform::Platform* platform_;
  float clear_color_[4];
  int width_, height_;
  const char* glsl_version_;
};

}  // namespace vkrt::renderer

#endif // OPENGLRENDERER_H