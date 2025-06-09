// STL
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// src
#include "Core/Application.h"
#include "Renderer/RendererTypes.h"
#include "Platform/PlatformTypes.h"

int main(int argc, char* argv[]) {
  // Application settings
  constexpr vkrt::renderer::Type renderer_type{ vkrt::renderer::Type::OpenGL };
  constexpr vkrt::platform::Type platform_type{ vkrt::platform::Type::SDL3 };
  const std::string window_title{ "vkRT Application" };
  constexpr int window_width{ 1280 };
  constexpr int window_height{ 720 };

  // Initialize application
  vkrt::Application application{};
  if (!application.Initialize(renderer_type, platform_type,
                              window_title, window_width, window_height)) {
    spdlog::critical("Failed to initialize application.");
    application.Shutdown();
    return 1;
  }

  // Run application
  application.Run();

  // Shutdown application
  application.Shutdown();

  return 0;
}
