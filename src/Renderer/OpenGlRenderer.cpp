#include "OpenGlRenderer.h"

// ImGui
#include "imgui_impl_opengl3.h"

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

Type OpenGlRenderer::type() const {
  return Type::OpenGL;
}

bool OpenGlRenderer::Initialize() {
  return true;
}

void OpenGlRenderer::Shutdown() {

}

bool OpenGlRenderer::InitializeImGui() const {
  return ImGui_ImplOpenGL3_Init();
}

void OpenGlRenderer::BeginNewImGuiFrame() const {
  ImGui_ImplOpenGL3_NewFrame();
}

void OpenGlRenderer::RenderImGuiDrawData(ImDrawData* draw_data) const {
  ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

void OpenGlRenderer::ShutdownImGui() const {
  ImGui_ImplOpenGL3_Shutdown();
}

} // namespace renderer
} // namespace vkrt
