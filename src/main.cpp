// STL
#include <iostream>

// src
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  // Configure application
  vkrt::ApplicationConfig config{};
  config.platform_type = vkrt::platform::Type::GLFW;  // or Type::GLFW
  config.renderer_type = vkrt::renderer::Type::Vulkan; // or Type::Vulkan
  config.window_title = "vkRT - Vulkan Raytracing";
  config.window_width = 1280;
  config.window_height = 720;

  // Create and run application
  vkrt::Application application{config};

  if (!application.Initialize()) {
    std::cerr << "Failed to initialize application." << std::endl;
    return 1;
  }

  application.Run();

  // Shutdown is called automatically in destructor
  return 0;
}