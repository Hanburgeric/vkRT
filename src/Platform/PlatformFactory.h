#ifndef PLATFORMFACTORY_H
#define PLATFORMFACTORY_H

// STL
#include <memory>

// src
#include "Platform.h"
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

class Factory {
public:
  static std::unique_ptr<Platform> Create(Type type);

private:
  static std::unique_ptr<Platform> CreateSdl3();
  static std::unique_ptr<Platform> CreateGlfw();
};

}  // namespace platform
}  // namespace vkrt

#endif // PLATFORMFACTORY_H
