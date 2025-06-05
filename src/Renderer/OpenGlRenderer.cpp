#include "OpenGlRenderer.h"

// STL
#include <iostream>

// OpenGL
#if defined(_WIN32)
#include <windows.h>
#endif
#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

// ImGui
#include "imgui.h"
#include "imgui_impl_opengl3.h"

// src
#include "../Platform/Platform.h"

namespace vkrt::renderer {

OpenGlRenderer::OpenGlRenderer()
    : platform_(nullptr)
    , clear_color_{0.45f, 0.55f, 0.60f, 1.00f}
    , width_(1280)
    , height_(720)
    , glsl_version_(nullptr) {
}

OpenGlRenderer::~OpenGlRenderer() {
    Shutdown();
}

bool OpenGlRenderer::Initialize(const RendererCreateInfo& info) {
    platform_ = info.platform;
    width_ = info.width;
    height_ = info.height;

    if (!platform_) {
        std::cerr << "OpenGL Renderer: Platform is null" << std::endl;
        return false;
    }

    // Make OpenGL context current
    platform_->MakeContextCurrent();

    // Determine GLSL version
#if defined(__APPLE__)
    glsl_version_ = "#version 150";
#else
    glsl_version_ = "#version 130";
#endif

    return true;
}

void OpenGlRenderer::Shutdown() {
    platform_ = nullptr;
}

void OpenGlRenderer::NewFrame() {
    if (!platform_) return;

    // Get current framebuffer size for viewport
    int display_w, display_h;
    platform_->GetFramebufferSize(display_w, display_h);

    if (display_w != width_ || display_h != height_) {
        OnResize(display_w, display_h);
    }

    // Call ImGui OpenGL NewFrame to build font atlas if needed
    ImGui_ImplOpenGL3_NewFrame();
}

void OpenGlRenderer::RenderFrame(ImDrawData* draw_data) {
    if (!draw_data) return;

    // Setup viewport
    glViewport(0, 0, width_, height_);

    // Clear
    glClearColor(clear_color_[0] * clear_color_[3],
                 clear_color_[1] * clear_color_[3],
                 clear_color_[2] * clear_color_[3],
                 clear_color_[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render ImGui
    ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

void OpenGlRenderer::Present() {
    if (platform_) {
        platform_->SwapBuffers();
    }
}

void OpenGlRenderer::OnResize(int width, int height) {
    width_ = width;
    height_ = height;
    glViewport(0, 0, width, height);
}

void OpenGlRenderer::SetClearColor(float r, float g, float b, float a) {
    clear_color_[0] = r;
    clear_color_[1] = g;
    clear_color_[2] = b;
    clear_color_[3] = a;
}

bool OpenGlRenderer::InitializeImGui() {
    return ImGui_ImplOpenGL3_Init(glsl_version_);
}

void OpenGlRenderer::ShutdownImGui() {
    ImGui_ImplOpenGL3_Shutdown();
}

}  // namespace vkrt::renderer