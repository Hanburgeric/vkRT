#include "Application.h"

// STL
#include <iostream>

void Application::Init() {
  std::cout << "Application initializing." << std::endl;
}

void Application::Iterate() {
  std::cout << "Application iterating." << std::endl;
}

void Application::Quit() {
  std::cout << "Application quitting." << std::endl;
}
