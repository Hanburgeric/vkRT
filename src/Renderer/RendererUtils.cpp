#include "RendererUtils.h"

// STL
#include <string>

// src
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {
namespace utils {

std::string TypeToString(Type renderer_type) {
  switch (renderer_type) {
    case Type::Vulkan: { return "Vulkan"; }
    case Type::OpenGL: { return "OpenGL"; }
    default: { return "Unknown"; }
  }
}

} // namespace utils
} // namespace renderer
} // namespace vkrt
