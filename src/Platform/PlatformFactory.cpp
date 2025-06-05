#include "PlatformFactory.h"

// src
#include "Sdl3Platform.h"
#include "GlfwPlatform.h"

namespace vkrt::platform {

std::unique_ptr<Platform> Factory::Create(Type type) {
  switch (type) {
    case Type::SDL3: { return CreateSdl3(); }
    case Type::GLFW: { return CreateGlfw(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Platform> Factory::CreateSdl3() {
  return std::make_unique<Sdl3Platform>();
}

std::unique_ptr<Platform> Factory::CreateGlfw() {
  return std::make_unique<GlfwPlatform>();
}

}  // namespace vkrt::platform