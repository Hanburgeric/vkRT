#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

// src
#include "Platform.h"

namespace vkrt {
namespace platform {

class Sdl3Platform : public Platform {
public:
  bool Initialize() override;
  void Shutdown() override;
};

} // namespace platform
} // namespace vkrt

#endif // SDL3PLATFORM_H
