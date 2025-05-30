#ifndef APPLICATION_H
#define APPLICATION_H

// SDL
#include "SDL3/SDL.h"

class Application {
public:
  Application();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  bool InitializeSdl();
  bool InitializeImGui();

  void ShutdownSdl();
  void ShutdownImGui();

  void HandleEvents();
  void UpdatePhysics();
  void RenderViewport();

private:
  SDL_Window* window_;
  bool should_quit_;
};

#endif //APPLICATION_H
