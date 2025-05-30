#include <iostream>

// src
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  Application* application{ new Application };
  if (!application) {
    std::cerr << "Failed to create application." << std::endl;
    return 1;
  }

  application->Init();
  application->Iterate();
  application->Quit();

  return 0;
}
