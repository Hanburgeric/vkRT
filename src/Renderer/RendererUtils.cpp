#include "RendererUtils.h"

namespace vkrt {
namespace renderer {
namespace utils {

std::string ToString(Type type) {
  switch (type) {
    case Type::Vulkan: { return "Vulkan"; }
    case Type::OpenGL: { return "OpenGL"; }
    default: { return "unknown"; }
  }
}

}  // namespace utils
}  // namespace renderer
}  // namespace vkrt
