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

std::unique_ptr<Platform> Factory::CreatePlatform(Type platform_type) {
  switch (platform_type) {
    case Type::SDL3: { return CreateSdl3Platform(); }
    case Type::GLFW: { return CreateGlfwPlatform(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Platform> Factory::CreateSdl3Platform() {
  return std::make_unique<Sdl3Platform>();
}

std::unique_ptr<Platform> Factory::CreateGlfwPlatform() {
  return std::make_unique<GlfwPlatform>();
}

} // namespace platform
} // namespace vkrt
