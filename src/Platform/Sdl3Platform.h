#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class Sdl3Platform : public Platform {
public:
  constexpr Type type() const override { return Type::SDL3; }

  bool Initialize(const renderer::Renderer& renderer) override;
  void Shutdown() override;

private:
  bool InitializeForVulkan(const renderer::Renderer& renderer);
  bool InitializeForOpenGl(const renderer::Renderer& renderer);
};

} // namespace platform
} // namespace vkrt

#endif // SDL3PLATFORM_H
