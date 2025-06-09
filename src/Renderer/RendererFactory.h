#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

// STL
#include <memory>

// src
#include "RendererTypes.h"

// Forward declarations
namespace vkrt::renderer { class Renderer; }

namespace vkrt {
namespace renderer {

class Factory {
public:
  static std::unique_ptr<Renderer> CreateRenderer(Type type);

private:
  static std::unique_ptr<Renderer> CreateVulkanRenderer();
  static std::unique_ptr<Renderer> CreateOpenGlRenderer();
};

} // namespace renderer
} // namespace vkrt

#endif // RENDERERFACTORY_H
