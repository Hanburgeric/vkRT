#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// STL
#include <string>

// SDL3
#include "SDL3/SDL.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class Sdl3Platform : public Platform {
public:
  constexpr Type type() const override { return Type::SDL3; }

  bool Initialize(const renderer::Renderer& renderer,
                  const std::string& window_title,
                  int window_width, int window_height) override;
  bool ShouldQuit() const override;
  void HandleEvents() override;
  void Shutdown() override;

private:
  bool InitializeForVulkan(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);
  bool InitializeForOpenGl(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);

private:
  bool initialized_;
  SDL_Window* window_;
  bool should_quit_;
};

} // namespace platform
} // namespace vkrt

#endif // SDL3PLATFORM_H
