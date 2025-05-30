// STL
#include <iostream>

// src
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  // Initialize application
  vkrt::Application application{};
  if (!application.Initialize()) {
    std::cerr << "Failed to initialize application." << std::endl;
    return 1;
  }

  // Run application
  application.Run();

  // Shut down application
  application.Shutdown();

  return 0;
}
