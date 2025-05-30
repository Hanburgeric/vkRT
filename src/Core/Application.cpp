#include "Application.h"

// STL
#include <iostream>

// SDL
#include "SDL3/SDL.h"

// ImGui
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_vulkan.h"

Application::Application()
    : window_{ nullptr }
    , should_quit_{ false } {
}

bool Application::Initialize() {
  // Initialize SDL
  if (!InitializeSdl()) {
    return false;
  }

  // Initialize ImGui
  if (!InitializeImGui()) {
    return false;
  }

  return true;
}

void Application::Run() {
  while (!should_quit_) {
    HandleEvents();
    UpdatePhysics();
    RenderViewport();
  }
}

void Application::Shutdown() {
  // Shutdown ImGui
  ShutdownImGui();

  // Shutdown SDL
  ShutdownSdl();
}

bool Application::InitializeSdl() {
  // Initialize SDL
  constexpr SDL_InitFlags init_flags{ SDL_INIT_VIDEO };
  if (!SDL_Init(init_flags)) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  // Create window
  constexpr SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN
  };
  window_ = SDL_CreateWindow("vkRT", 1280, 720, window_flags);
  if (!window_) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool Application::InitializeImGui() {
  // ???
  // IMGUI_CHECKVERSION();
  // ImGui::CreateContext();
  // ImGuiIO& io{ ImGui::GetIO() };
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // ???
  // ImGui_ImplSDL3_InitForVulkan(window_);
  // ImGui_ImplVulkan_InitInfo init_info{};
  // ImGui_ImplVulkan_Init(&init_info);

  return true;
}

void Application::ShutdownSdl() {
  // Destroy window
  if (window_) {
    SDL_DestroyWindow(window_);
  }

  // Shutdown SDL
  SDL_Quit();
}

void Application::ShutdownImGui() {

}

void Application::HandleEvents() {
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    // ???
    // ImGui_ImplSDL3_ProcessEvent(&event);

    // ???
    switch (event.type) {
      case SDL_EVENT_QUIT: {
        should_quit_ = true;
        break;
      }
      default: {
        break;
      }
    }

    // ???
    // ImGui_ImplVulkan_NewFrame();
    // ImGui_ImplSDL3_NewFrame();
    // ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
  }
}

void Application::UpdatePhysics() {

}

void Application::RenderViewport() {
  // ???

  // ???
  // ImGui::Render();
  // ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData, ???);
}
