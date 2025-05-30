#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

// STL
#include <string>

namespace vkrt {
namespace renderer {

enum class Api {
  Vulkan, OpenGL
};

std::string ApiToString(Api api) {
  switch (api) {
    case Api::Vulkan: return "Vulkan";
    case Api::OpenGL: return "OpenGL";
    default: return "Unknown";
  }
}

class Interface {
public:
  virtual ~Interface() = default;
};

}
}

#endif //RENDERERINTERFACE_H
