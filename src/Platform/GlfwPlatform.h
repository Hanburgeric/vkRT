#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// src
#include "Platform.h"
#include "PlatformTypes.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  Type type() const override;

  bool InitializeImGui() const override;
  void BeginNewImGuiFrame() const override;
  void ShutdownImGui() const override;
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
