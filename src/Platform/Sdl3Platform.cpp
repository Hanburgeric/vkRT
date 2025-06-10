#include "Sdl3Platform.h"

// STL
#include <memory>
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// SDL3
#include "SDL3/SDL.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/VulkanRenderer.h"
#include "../Renderer/OpenGlRenderer.h"

namespace vkrt {
namespace platform {

Sdl3Platform::~Sdl3Platform() {
  Sdl3Platform::Shutdown();
}

bool Sdl3Platform::Initialize(const renderer::Renderer& renderer,
                              const std::string& window_title, int window_width,
                              int window_height) {
  switch (renderer.type()) {
    case renderer::Type::Vulkan: {
      return InitializeForVulkan(renderer, window_title, window_width,
                                 window_height);
    }
    case renderer::Type::OpenGL: {
      return InitializeForOpenGl(renderer, window_title, window_width,
                                 window_height);
    }
    default: {
      return false;
    }
  }
}

bool Sdl3Platform::ShouldQuit() const {
  return should_quit_;
}

void Sdl3Platform::HandleEvents() {
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT: { should_quit_ = true; break; }
      default: { break; }
    }
  }
}

void Sdl3Platform::Shutdown() {
  // Destroy window
  if (window_) {
    window_.reset();
  }

  // Shutdown
  if (initialized_) {
    SDL_Quit();
  }
}

bool Sdl3Platform::InitializeForVulkan(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  return false;
}

bool Sdl3Platform::InitializeForOpenGl(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  // Initialize SDL3
  constexpr SDL_InitFlags init_flags{
    SDL_INIT_VIDEO
  };
  initialized_ = SDL_Init(init_flags);
  if (!initialized_) {
    spdlog::error("Failed to initialize SDL: {0}", SDL_GetError());
    return false;
  }

  // Create window
  constexpr SDL_WindowFlags window_flags{
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };
  window_ = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
    SDL_CreateWindow(window_title.c_str(),
                     window_width, window_height,
                     window_flags),
    SDL_DestroyWindow
  );
  if (!window_) {
    spdlog::error("Failed to create SDL window: {0}", SDL_GetError());
    return false;
  }

  return true;
}

} // namespace platform
} // namespace vkrt
