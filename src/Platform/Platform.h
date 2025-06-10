#ifndef PLATFORM_H
#define PLATFORM_H

// STL
#include <string>

// src
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class Platform {
public:
  virtual ~Platform() = default;

  virtual constexpr Type type() const = 0;

  virtual bool Initialize(const renderer::Renderer& renderer,
                          const std::string& window_title,
                          int window_width, int window_height) = 0;
  virtual bool ShouldQuit() const = 0;
  virtual void HandleEvents() = 0;
  virtual void Shutdown() = 0;
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORM_H
