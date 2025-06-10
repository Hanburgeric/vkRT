#include "GlfwPlatform.h"

// STL
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// GLFW
#include "GLFW/glfw3.h"

// src
#include "Platform.h"
#include "PlatformTypes.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/VulkanRenderer.h"
#include "../Renderer/OpenGlRenderer.h"

namespace vkrt {
namespace platform {

bool GlfwPlatform::Initialize(const renderer::Renderer& renderer,
                              const std::string& window_title, int window_width,
                              int window_height) {
  switch (renderer.type()) {
    case renderer::Type::Vulkan: {
      return InitializeForVulkan(renderer, window_title, window_width,
                                 window_height);
    }
    case renderer::Type::OpenGL: {
      return InitializeForOpenGl(renderer, window_title, window_width,
                                 window_height);
    }
    default: {
      return false;
    }
  }
}
bool GlfwPlatform::ShouldQuit() const {
  return true;
}

void GlfwPlatform::HandleEvents() {
}

void GlfwPlatform::Shutdown() {
}

bool GlfwPlatform::InitializeForVulkan(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  return false;
}

bool GlfwPlatform::InitializeForOpenGl(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  return true;
}

} // namespace platform
} // namespace vkrt
