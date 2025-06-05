#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

// Vulkan
#include <vulkan/vulkan.h>

// src
#include "Platform.h"

namespace vkrt::platform {

class Sdl3Platform : public Platform {
public:
  Sdl3Platform();
  ~Sdl3Platform() override;

  bool Initialize(const PlatformCreateInfo& info) override;
  void Shutdown() override;

  bool ShouldClose() const override;
  void PollEvents() override;
  void SwapBuffers() override;

  WindowInfo GetWindowInfo() const override;
  void GetFramebufferSize(int& width, int& height) const override;

  // ImGui integration
  bool InitializeImGui() override;
  void ShutdownImGui() override;
  void NewFrame() override;
  bool ProcessEvent(void* event) override;

  // Renderer-specific functionality
  void* GetRequiredInstanceExtensions(uint32_t& count) override;
  bool CreateSurface(void* instance, void* allocator, void* surface) override;
  void MakeContextCurrent() override;

private:
  SDL_Window* window_;
  SDL_GLContext gl_context_;
  renderer::Type renderer_type_;
  bool should_close_;
  int width_, height_;
};

}  // namespace vkrt::platform

#endif // SDL3PLATFORM_H