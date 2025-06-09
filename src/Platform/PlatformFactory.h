#ifndef PLATFORMFACTORY_H
#define PLATFORMFACTORY_H

// STL
#include <memory>

// src
#include "Platform.h"
#include "PlatformTypes.h"

// Forward declarations
namespace vkrt::platform { class Platform; }

namespace vkrt {
namespace platform {

class Factory {
public:
  static std::unique_ptr<Platform> CreatePlatform(Type platform_type);

private:
  static std::unique_ptr<Platform> CreateSdl3Platform();
  static std::unique_ptr<Platform> CreateGlfwPlatform();
};

} // namespace platform
} // namespace vkrt

#endif // PLATFORMFACTORY_H
