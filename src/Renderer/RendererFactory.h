#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

// STL
#include <memory>

// src
#include "Renderer.h"
#include "RendererTypes.h"

namespace vkrt {
namespace renderer {

class Factory {
public:
  static std::unique_ptr<Renderer> CreateRenderer(Type renderer_type);

private:
  static std::unique_ptr<Renderer> CreateVulkanRenderer();
  static std::unique_ptr<Renderer> CreateOpenGlRenderer();
};

} // namespace renderer
} // namespace vkrt

#endif // RENDERERFACTORY_H
