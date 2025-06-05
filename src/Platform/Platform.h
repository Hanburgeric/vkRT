#ifndef PLATFORM_H
#define PLATFORM_H

// src
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

class Platform {
public:
  virtual ~Platform() = default;

  virtual Type type() const = 0;

  virtual bool InitializeImGui() const = 0;
  virtual void BeginNewImGuiFrame() const = 0;
  virtual void ShutdownImGui() const = 0;
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORM_H
