#ifndef PLATFORM_H
#define PLATFORM_H

// src
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class Platform {
public:
  virtual ~Platform() = default;

  virtual constexpr Type type() const = 0;

  virtual bool Initialize(const renderer::Renderer& renderer) = 0;
  virtual void Shutdown() = 0;
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORM_H
