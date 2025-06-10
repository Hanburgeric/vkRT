#ifndef GLFWPLATFORM_H
#define GLFWPLATFORM_H

// STL
#include <memory>
#include <string>

// GLFW
#include "GLFW/glfw3.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"

namespace vkrt {
namespace platform {

class GlfwPlatform : public Platform {
public:
  GlfwPlatform() = default;
  ~GlfwPlatform() override;

  GlfwPlatform(const GlfwPlatform&) = delete;
  GlfwPlatform& operator=(const GlfwPlatform&) = delete;

  GlfwPlatform(GlfwPlatform&&) = default;
  GlfwPlatform& operator=(GlfwPlatform&&) = default;

  constexpr Type type() const override { return Type::GLFW; }

  bool Initialize(const renderer::Renderer& renderer,
                  const std::string& window_title,
                  int window_width, int window_height) override;
  bool ShouldQuit() const override;
  void HandleEvents() override;
  void Shutdown() override;

private:
  bool InitializeForVulkan(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);
  bool InitializeForOpenGl(const renderer::Renderer& renderer,
                           const std::string& window_title,
                           int window_width, int window_height);

private:
  bool initialized_{ false };
  std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window_{
    nullptr, glfwDestroyWindow
  };
};

} // namespace platform
} // namespace vkrt

#endif // GLFWPLATFORM_H
