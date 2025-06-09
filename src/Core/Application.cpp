#include "Application.h"

// STL
#include <memory>
#include <string>

// src
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/RendererFactory.h"

#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"
#include "../Platform/PlatformFactory.h"

namespace vkrt {

Application::Application()
    : renderer_{ nullptr }
    , platform_{ nullptr } {}

bool Application::Initialize(renderer::Type renderer_type,
                             platform::Type platform_type,
                             const std::string& window_title, int window_width,
                             int window_height) {
  // Create renderer
  renderer_ = renderer::Factory::CreateRenderer(renderer_type);
  if (!renderer_) {
    // Log or throw
    return false;
  }

  // Initialize renderer
  if (!renderer_->Initialize()) {
    // Log or throw
    return false;
  }

  // Create platform
  platform_ = platform::Factory::CreatePlatform(platform_type);
  if (!platform_) {
    // Log or throw
    return false;
  }

  // Initialize platform
  if (!platform_->Initialize()) {
    // Log or throw
    return false;
  }
}

void Application::Run() {
  while (!platform_->ShouldQuit()) {
    platform_->HandleEvents();
  }
}

void Application::Shutdown() {
  // Shutdown platform
  if (platform_) {
    platform_->Shutdown();
  }

  // Shutdown renderer
  if (renderer_) {
    renderer_->Shutdown();
  }
}

} // namespace vkrt
