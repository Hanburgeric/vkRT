#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// SDL3
#include <SDL3/SDL.h>

// src
#include "Platform.h"
#include "PlatformTypes.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {
namespace platform {

class Sdl3Platform : public Platform {
public:
  Type type() const override;

  bool Initialize(vkrt::renderer::Type renderer_type) override;
  bool ShouldQuit() const override;
  void HandleEvents() override;
  void Shutdown() override;

  bool InitializeImGui(vkrt::renderer::Type renderer_type) const override;
  void BeginNewImGuiFrame() const override;
  void ShutdownImGui() const override;

private:
  SDL_Window* window_;
  SDL_Event event_;
  bool should_quit_;
};

} // namespace platform
} // namespace vkrt

#endif // SDL3PLATFORM_H
