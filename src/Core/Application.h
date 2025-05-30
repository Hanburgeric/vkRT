#ifndef APPLICATION_H
#define APPLICATION_H

// STL
#include <memory>

// SDL
#include "SDL3/SDL.h"

// src
#include "../Renderer/RendererInterface.h"

namespace vkrt {

class Application {
public:
  Application();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  bool InitializeSdl();
  bool InitializeRenderer();
  bool InitializeImGui();

  void ShutdownSdl();
  void ShutdownRenderer();
  void ShutdownImGui();

  void HandleEvents();
  void UpdatePhysics();
  void RenderViewport();

private:
  SDL_Window* window_;
  std::unique_ptr<renderer::Interface> renderer_;
  bool should_quit_;
};

}

#endif //APPLICATION_H
