// spdlog
#include "spdlog/spdlog.h"

// src
#include "Application.h"

int main(int argc, char* argv[]) {
  vkrt::Application application{};
  if (!application.Initialize()) {
    spdlog::error("Failed to initialize vkrt application.");
    return 1;
  }

  application.Run();

  return 0;
}
