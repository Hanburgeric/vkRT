#include "PlatformFactory.h"

namespace vkrt {
namespace platform {

std::unique_ptr<Platform> Factory::Create(Type type) {
  switch (type) {
    case Type::SDL3: { return CreateSdl3(); }
    case Type::GLFW: { return CreateGlfw(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Platform> Factory::CreateSdl3() {
  return nullptr;
}

std::unique_ptr<Platform> Factory::CreateGlfw() {
  return nullptr;
}

}  // namespace platform
}  // namespace vkrt
