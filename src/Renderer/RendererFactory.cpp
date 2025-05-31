#include "RendererFactory.h"

namespace vkrt {
namespace renderer {

std::unique_ptr<Renderer> Factory::Create(Type type) {
  switch (type) {
    case Type::Vulkan: { return CreateVulkan(); }
    case Type::OpenGL: { return CreateOpenGl(); }
    default: { return nullptr; }
  }
}

std::unique_ptr<Renderer> Factory::CreateVulkan() {
  return nullptr;
}

std::unique_ptr<Renderer> Factory::CreateOpenGl() {
  return nullptr;
}

}  // namespace renderer
}  // namespace vkrt
