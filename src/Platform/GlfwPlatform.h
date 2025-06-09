#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// src
#include "Platform.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  bool Initialize() override;
  void Shutdown() override;
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
