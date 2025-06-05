#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// src
#include "Platform.h"
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

class Sdl3Platform : public Platform {
public:
  Type type() const override;

  bool InitializeImGui() const override;
  void BeginNewImGuiFrame() const override;
  void ShutdownImGui() const override;
};

} // namespace platform
} // namespace vkrt

#endif // SDL3PLATFORM_H
