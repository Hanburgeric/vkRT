#include "Application.h"

// STL
#include <iostream>
#include <memory>

// ImGui
#include "imgui.h"

// src
#include "../Platform/PlatformTypes.h"
#include "../Platform/PlatformFactory.h"
#include "../Platform/PlatformUtils.h"
#include "../Renderer/RendererTypes.h"
#include "../Renderer/RendererFactory.h"
#include "../Renderer/RendererUtils.h"

namespace vkrt {

Application::Application(const ApplicationConfig& config)
    : config_(config)
    , platform_(nullptr)
    , renderer_(nullptr)
    , running_(false)
    , show_demo_window_(true)
    , show_another_window_(false)
    , clear_color_(0.45f, 0.55f, 0.60f, 1.00f) {
}

Application::~Application() {
    if (running_) {
        Shutdown();
    }
}

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

    running_ = true;
    return true;
}

void Application::Run() {
    std::cout << "Application running..." << std::endl;

    while (running_ && !platform_->ShouldClose()) {
        MainLoop();
    }
}

void Application::Shutdown() {
    running_ = false;

    // Shutdown in reverse order of initialization
    ShutdownImGui();
    ShutdownRenderer();
    ShutdownPlatform();
}

bool Application::InitializePlatform() {
    platform_ = platform::Factory::Create(config_.platform_type);

    if (!platform_) {
        std::cerr << "Failed to create "
                  << platform::utils::ToString(config_.platform_type)
                  << " platform." << std::endl;
        return false;
    }

    platform::PlatformCreateInfo info{};
    info.window_title = config_.window_title;
    info.window_width = config_.window_width;
    info.window_height = config_.window_height;
    info.renderer_type = config_.renderer_type;

    if (!platform_->Initialize(info)) {
        std::cerr << "Failed to initialize platform." << std::endl;
        return false;
    }

    return true;
}

bool Application::InitializeRenderer() {
    renderer_ = renderer::Factory::Create(config_.renderer_type);

    if (!renderer_) {
        std::cerr << "Failed to create "
                  << renderer::utils::ToString(config_.renderer_type)
                  << " renderer." << std::endl;
        return false;
    }

    renderer::RendererCreateInfo info{};
    info.platform = platform_.get();
    info.width = config_.window_width;
    info.height = config_.window_height;

    if (!renderer_->Initialize(info)) {
        std::cerr << "Failed to initialize renderer." << std::endl;
        return false;
    }

    return true;
}

bool Application::InitializeImGui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if (!platform_->InitializeImGui()) {
        std::cerr << "Failed to initialize ImGui platform backend." << std::endl;
        return false;
    }

    if (!renderer_->InitializeImGui()) {
        std::cerr << "Failed to initialize ImGui renderer backend." << std::endl;
        return false;
    }

    return true;
}

void Application::ShutdownPlatform() {
    if (platform_) {
        platform_->Shutdown();
        platform_.reset();
    }
}

void Application::ShutdownRenderer() {
    if (renderer_) {
        renderer_->Shutdown();
        renderer_.reset();
    }
}

void Application::ShutdownImGui() {
    // Shutdown ImGui renderers first
    if (renderer_) {
        renderer_->ShutdownImGui();
    }

    // Then shutdown platform
    if (platform_) {
        platform_->ShutdownImGui();
    }

    // Finally destroy ImGui context
    ImGui::DestroyContext();
}

void Application::MainLoop() {
    HandleEvents();
    RenderFrame();
}

void Application::HandleEvents() {
    platform_->PollEvents();
}

void Application::RenderFrame() {
    // Start the Dear ImGui frame (correct order)
    platform_->NewFrame();  // Platform first
    renderer_->NewFrame();   // Then renderer
    ImGui::NewFrame();       // Finally ImGui

    RenderImGui();

    // Rendering
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();

    renderer_->SetClearColor(clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w);
    renderer_->RenderFrame(draw_data);
    renderer_->Present();
}

void Application::RenderImGui() {
    // 1. Show the big demo window
    if (show_demo_window_) {
        ImGui::ShowDemoWindow(&show_demo_window_);
    }

    // 2. Show a simple window that we create ourselves
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window_);
        ImGui::Checkbox("Another Window", &show_another_window_);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color_);

        if (ImGui::Button("Button")) {
            counter++;
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                   1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window
    if (show_another_window_) {
        ImGui::Begin("Another Window", &show_another_window_);
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me")) {
            show_another_window_ = false;
        }
        ImGui::End();
    }
}

}  // namespace vkrt