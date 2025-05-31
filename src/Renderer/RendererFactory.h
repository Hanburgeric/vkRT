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
  static std::unique_ptr<Renderer> Create(Type type);

private:
  static std::unique_ptr<Renderer> CreateVulkan();
  static std::unique_ptr<Renderer> CreateOpenGl();
};

}  // namespace renderer
}  // namespace vkrt

#endif // RENDERERFACTORY_H
