#include "PlatformUtils.h"

// STL
#include <string>

// src
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {
namespace utils {

std::string TypeToString(Type type) {
  switch (type) {
    case Type::SDL3: return "SDL3";
    case Type::GLFW: return "GLFW";
    default: return "Unknown";
  }
}

} // namespace utils
} // namespace platform
} // namespace vkrt
