#include "PlatformUtils.h"

namespace vkrt {
namespace platform {
namespace utils {

std::string ToString(Type type) {
  switch (type) {
    case Type::SDL3: { return "SDL3"; }
    case Type::GLFW: { return "GLFW"; }
    default: { return "unknown"; }
  }
}

}  // namespace utils
}  // namespace platform
}  // namespace vkrt
