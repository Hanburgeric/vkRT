#ifndef PLATFORM_H
#define PLATFORM_H

// STL
#include <string>

// src
#include "../Renderer/RendererTypes.h"

namespace vkrt::platform {

struct WindowInfo {
  void* window = nullptr;
  void* context = nullptr;  // For OpenGL context
  int width = 1280;
  int height = 720;
};

struct PlatformCreateInfo {
  const char* window_title = "vkRT";
  int window_width = 1280;
  int window_height = 720;
  renderer::Type renderer_type = renderer::Type::Vulkan;
};

class Platform {
public:
  virtual ~Platform() = default;

  virtual bool Initialize(const PlatformCreateInfo& info) = 0;
  virtual void Shutdown() = 0;

  virtual bool ShouldClose() const = 0;
  virtual void PollEvents() = 0;
  virtual void SwapBuffers() = 0;

  virtual WindowInfo GetWindowInfo() const = 0;
  virtual void GetFramebufferSize(int& width, int& height) const = 0;

  // ImGui integration
  virtual bool InitializeImGui() = 0;
  virtual void ShutdownImGui() = 0;
  virtual void NewFrame() = 0;
  virtual bool ProcessEvent(void* event) = 0;

  // Renderer-specific functionality
  virtual void* GetRequiredInstanceExtensions(uint32_t& count) = 0;  // For Vulkan
  virtual bool CreateSurface(void* instance, void* allocator, void* surface) = 0;  // For Vulkan
  virtual void MakeContextCurrent() = 0;  // For OpenGL
};

}  // namespace vkrt::platform

#endif // PLATFORM_H