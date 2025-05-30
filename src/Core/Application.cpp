#include "Application.h"

// STL
#include <iostream>
#include <memory>

// src
#include "../Platform/Platform.h"
#include "../Platform/PlatformTypes.h"
#include "../Platform/PlatformUtils.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/RendererUtils.h"

namespace vkrt {

Application::Application()
    : platform_type_{ platform::Type::SDL3 }
    , platform_{ nullptr }
    , renderer_type_{ renderer::Type::Vulkan }
    , renderer_{ nullptr }
{}

bool Application::Initialize() {
  if (!InitializePlatform()) {
    std::cerr << "Failed to initialize platform." << std::endl;
    return false;
  }

  if (!InitializeRenderer()) {
    std::cerr << "Failed to initialize renderer." << std::endl;
    return false;
  }

  if (!InitializeImGui()) {
    std::cerr << "Failed to initialize ImGui." << std::endl;
    return false;
  }

  return true;
}

void Application::Run() {
  std::cout << "Application running..." << std::endl;
}

void Application::Shutdown() {
  ShutdownImGui();
  ShutdownRenderer();
  ShutdownPlatform();
}

bool Application::InitializePlatform() {
  //platform_ = platform::Factory::CreatePlatform(platform_type_);

  if (!platform_) {
    std::cerr << "Failed to create "
              << platform::utils::ToString(platform_type_)
              << " platform." << std::endl;

    return false;
  }

  return true;
}

bool Application::InitializeRenderer() {
  //renderer_ = renderer::Factory::CreateRenderer(renderer_type_);

  if (!renderer_) {
    std::cerr << "Failed to create "
              << renderer::utils::ToString(renderer_type_)
              << " renderer." << std::endl;

    return false;
  }

  return true;
}

bool Application::InitializeImGui() {
  return true;
}

void Application::ShutdownPlatform() {
}

void Application::ShutdownRenderer() {
}

void Application::ShutdownImGui() {
}

}  // namespace vkrt
