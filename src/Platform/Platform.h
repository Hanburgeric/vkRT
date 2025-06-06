#ifndef PLATFORM_H
#define PLATFORM_H

// src
#include "PlatformTypes.h"
#include "../Renderer/RendererTypes.h"

namespace vkrt {
namespace platform {

class Platform {
public:
  virtual ~Platform() = default;

  virtual Type type() const = 0;

  virtual bool Initialize(vkrt::renderer::Type renderer_type) = 0;
  virtual bool ShouldQuit() const = 0;
  virtual void HandleEvents() = 0;
  virtual void Shutdown() = 0;

  virtual bool InitializeImGui(vkrt::renderer::Type renderer_type) const = 0;
  virtual void BeginNewImGuiFrame() const = 0;
  virtual void ShutdownImGui() const = 0;
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORM_H
