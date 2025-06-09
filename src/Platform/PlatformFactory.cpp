#include "PlatformFactory.h"

// STL
#include <memory>

// src
#include "Platform.h"
#include "PlatformTypes.h"
#include "Sdl3Platform.h"
#include "GlfwPlatform.h"

namespace vkrt {
namespace platform {

std::unique_ptr<Platform> Factory::CreatePlatform(Type type) {
  switch (type) {
    case Type::SDL3: { return CreateSdl3Platform(); }
    case Type::GLFW: { return CreateGlfwPlatform(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Platform> Factory::CreateSdl3Platform() {
  return nullptr;
}

std::unique_ptr<Platform> Factory::CreateGlfwPlatform() {
  return nullptr;
}

} // namespace platform
} // namespace vkrt
