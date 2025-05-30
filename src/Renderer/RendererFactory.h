#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

// STL
#include <memory>

// src
#include "RendererInterface.h"

namespace vkrt {
namespace renderer {

class Factory {
public:
  static std::unique_ptr<Interface> CreateRenderer(Api api);

private:
  static std::unique_ptr<Interface> CreateVulkanRenderer();
  static std::unique_ptr<Interface> CreateOpenGLRenderer();
};

}
}

#endif //RENDERERFACTORY_H
