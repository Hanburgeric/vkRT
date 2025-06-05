#include "Application.h"

// STL
#include <iostream>

// ImGui
#include "imgui.h"

// src
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererUtils.h"
#include "../Platform/Platform.h"
#include "../Platform/PlatformUtils.h"

namespace vkrt {

Application::Application()
    : renderer_{ nullptr }
    , platform_{ nullptr }
    , imgui_context_{ nullptr } {}

bool Application::Initialize() {
  // Initialize renderer
  // ???

  // Initialize platform (using the renderer)
  // ???

  // Check ImGui version
  if (!IMGUI_CHECKVERSION()) {
    std::cerr << "IMGUI_CHECKVERSION() failed." << std::endl;
    return false;
  }

  // Create ImGui context
  imgui_context_ = ImGui::CreateContext();
  if (!imgui_context_) {
    std::cerr << "Failed to create ImGui context." << std::endl;
    return false;
  }

  // Configure ImGui
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Initialize ImGui for platform
  if (!platform_->InitializeImGui()) {
    std::cerr << platform::utils::TypeToString(platform_->type())
              << " platform failed to initialize ImGui." << std::endl;
    return false;
  }

  // Initialize ImGui for renderer
  if (!renderer_->InitializeImGui()) {
    std::cerr << renderer::utils::TypeToString(renderer_->type())
              << " renderer failed to initialize ImGui." << std::endl;
    return false;
  }

  return true;
}

void Application::Run() {
  while (!platform_->ShouldQuit()) {
    // Handle events
    platform_->PollEvents();
    platform_->ProcessImGuiEvents();
    // process events here

    // Begin new ImGui frame
    renderer_->BeginNewImGuiFrame();
    platform_->BeginNewImGuiFrame();
    ImGui::NewFrame();

    // replace with actual windows used by the application
    ImGui::ShowDemoWindow();

    // implement update functions

    // Render
    // clear framebuffer, render other stuff here
    ImGui::Render();
    renderer_->RenderImGuiDrawData(ImGui::GetDrawData());
    // swap backbuffers, etc. here
  }
}

void Application::Shutdown() {
  // Shutdown ImGui
  renderer_->ShutdownImGui();
  platform_->ShutdownImGui();
  ImGui::DestroyContext(imgui_context_);
  imgui_context_ = nullptr;

  // Shutdown and reset platform
  platform_->Shutdown();
  platform_.reset();

  // Shutdown and reset renderer
  renderer_->Shutdown();
  renderer_.reset();
}

} // namespace vkrt
