// STL
#include <iostream>

// src
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  vkrt::Application application{};
  if (!application.Initialize()) {
    std::cerr << "Failed to initialize vkRT application." << std::endl;
    return 1;
  }

  application.Run();
  application.Shutdown();

  return 0;
}
