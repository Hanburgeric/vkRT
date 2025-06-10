#include "Application.h"

// STL
#include <memory>
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// src
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/RendererFactory.h"
#include "../Renderer/RendererUtils.h"

#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"
#include "../Platform/PlatformFactory.h"
#include "../Platform/PlatformUtils.h"

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
    spdlog::error("Failed to create {0} renderer.",
                  renderer::utils::TypeToString(renderer_type));
    return false;
  }

  // Initialize renderer
  if (!renderer_->Initialize()) {
    spdlog::error("Failed to initialize {0}.",
                  renderer::utils::TypeToString(renderer_->type()));
    return false;
  }

  // Create platform
  platform_ = platform::Factory::CreatePlatform(platform_type);
  if (!platform_) {
    spdlog::error("Failed to create {0} platform.",
                  platform::utils::TypeToString(platform_type));
    return false;
  }

  // Initialize platform using the renderer
  if (!platform_->Initialize(*renderer_, window_title,
                             window_width, window_height )) {
    spdlog::error("Failed to initialize {0} with {1}.",
                  platform::utils::TypeToString(platform_->type()),
                  renderer::utils::TypeToString(renderer_->type()));
    return false;
  }

  return true;
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
