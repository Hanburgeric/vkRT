#include "Sdl3Platform.h"

// SDL3
#include <SDL3/SDL.h>

// ImGui
#include "imgui_impl_sdl3.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {
namespace platform {

Type Sdl3Platform::type() const {
  return Type::SDL3;
}

bool Sdl3Platform::Initialize(vkrt::renderer::Type renderer_type) {
  return true;
}

bool Sdl3Platform::ShouldQuit() const {
  return should_quit_;
}

void Sdl3Platform::HandleEvents() {
  while (SDL_PollEvent(&event_)) {
    // Allow ImGui to process the event first
    ImGui_ImplSDL3_ProcessEvent(&event_);

    // Allow SDL3 to process the event next
    switch (event_.type) {
      case SDL_EVENT_QUIT: {
        should_quit_ = true;
        break;
      }
    }
  }
}

void Sdl3Platform::Shutdown() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

bool Sdl3Platform::InitializeImGui(vkrt::renderer::Type renderer_type) const {
  switch (renderer_type) {
    case renderer::Type::Vulkan: {
      return ImGui_ImplSDL3_InitForVulkan(window_);
    }
    case renderer::Type::OpenGL: {
      return ImGui_ImplSDL3_InitForOpenGL(window_, nullptr);
    }
    default: {
      return false;
    }
  }
}

void Sdl3Platform::BeginNewImGuiFrame() const {
  ImGui_ImplSDL3_NewFrame();
}

void Sdl3Platform::ShutdownImGui() const {
  ImGui_ImplSDL3_Shutdown();
}

} // namespace platform
} // namespace vkrt
