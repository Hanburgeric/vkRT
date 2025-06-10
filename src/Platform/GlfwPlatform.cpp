#include "GlfwPlatform.h"

// STL
#include <memory>
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

GlfwPlatform::~GlfwPlatform() {
  GlfwPlatform::Shutdown();
}

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
  return glfwWindowShouldClose(window_.get());
}

void GlfwPlatform::HandleEvents() {
  glfwPollEvents();
}

void GlfwPlatform::Shutdown() {
  // Destroy window
  if (window_) {
    window_.reset();
  }

  // Shutdown
  if (initialized_) {
    glfwTerminate();
  }
}

bool GlfwPlatform::InitializeForVulkan(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  return false;
}

bool GlfwPlatform::InitializeForOpenGl(const renderer::Renderer& renderer,
                                       const std::string& window_title,
                                       int window_width, int window_height) {
  // Initialize GLFW
  initialized_ = glfwInit();
  if (!initialized_) {
    spdlog::error("Failed to initialize GLFW.");
    return false;
  }

  // Create window
  window_ = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(
    glfwCreateWindow(window_width, window_height, window_title.c_str(),
                     nullptr, nullptr),
    glfwDestroyWindow
  );
  if (!window_) {
    spdlog::error("Failed to create GLFW window");
    return false;
  }

  return true;
}

} // namespace platform
} // namespace vkrt
