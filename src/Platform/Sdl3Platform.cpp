#include "Sdl3Platform.h"

// ImGui
#include "imgui_impl_sdl3.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

Type Sdl3Platform::type() const {
  return Type::SDL3;
}

bool Sdl3Platform::InitializeImGui() const {
  return true;
}

void Sdl3Platform::BeginNewImGuiFrame() const {
  ImGui_ImplSDL3_NewFrame();
}

void Sdl3Platform::ShutdownImGui() const {
  ImGui_ImplSDL3_Shutdown();
}

} // namespace platform
} // namespace vkrt
