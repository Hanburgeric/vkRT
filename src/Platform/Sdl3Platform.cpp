#include "Sdl3Platform.h"

// STL
#include <iostream>

// SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

// Vulkan (for types in CreateSurface)
#include <vulkan/vulkan.h>

// ImGui
#include "imgui.h"
#include "imgui_impl_sdl3.h"

namespace vkrt::platform {

Sdl3Platform::Sdl3Platform()
    : window_(nullptr)
    , gl_context_(nullptr)
    , renderer_type_(renderer::Type::Vulkan)
    , should_close_(false)
    , width_(1280)
    , height_(720) {
}

Sdl3Platform::~Sdl3Platform() {
    Shutdown();
}

bool Sdl3Platform::Initialize(const PlatformCreateInfo& info) {
    renderer_type_ = info.renderer_type;
    width_ = info.window_width;
    height_ = info.window_height;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        std::cerr << "Error: SDL_Init(): " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    if (renderer_type_ == renderer::Type::Vulkan) {
        window_flags |= SDL_WINDOW_VULKAN;
    } else if (renderer_type_ == renderer::Type::OpenGL) {
        window_flags |= SDL_WINDOW_OPENGL;

        // Set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        // Decide GL+GLSL versions
#if defined(__APPLE__)
        // GL 3.2 Core + GLSL 150
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
    }

    // Create window
    window_ = SDL_CreateWindow(info.window_title, width_, height_, window_flags);
    if (!window_) {
        std::cerr << "Error: SDL_CreateWindow(): " << SDL_GetError() << std::endl;
        return false;
    }

    if (renderer_type_ == renderer::Type::OpenGL) {
        gl_context_ = SDL_GL_CreateContext(window_);
        if (!gl_context_) {
            std::cerr << "Error: SDL_GL_CreateContext(): " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GL_MakeCurrent(window_, gl_context_);
        SDL_GL_SetSwapInterval(1); // Enable vsync
    }

    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window_);

    return true;
}

void Sdl3Platform::Shutdown() {
    if (gl_context_) {
        SDL_GL_DestroyContext(gl_context_);
        gl_context_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    SDL_Quit();
}

bool Sdl3Platform::ShouldClose() const {
    return should_close_;
}

void Sdl3Platform::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) {
            should_close_ = true;
        }
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
            event.window.windowID == SDL_GetWindowID(window_)) {
            should_close_ = true;
        }
    }
}

void Sdl3Platform::SwapBuffers() {
    if (renderer_type_ == renderer::Type::OpenGL) {
        SDL_GL_SwapWindow(window_);
    }
}

WindowInfo Sdl3Platform::GetWindowInfo() const {
    WindowInfo info;
    info.window = window_;
    info.context = gl_context_;
    info.width = width_;
    info.height = height_;
    return info;
}

void Sdl3Platform::GetFramebufferSize(int& width, int& height) const {
    if (renderer_type_ == renderer::Type::OpenGL) {
        SDL_GetWindowSize(window_, &width, &height);
    } else {
        SDL_GetWindowSize(window_, &width, &height);
    }
}

bool Sdl3Platform::InitializeImGui() {
    if (renderer_type_ == renderer::Type::OpenGL) {
        return ImGui_ImplSDL3_InitForOpenGL(window_, gl_context_);
    } else if (renderer_type_ == renderer::Type::Vulkan) {
        return ImGui_ImplSDL3_InitForVulkan(window_);
    }
    return false;
}

void Sdl3Platform::ShutdownImGui() {
    ImGui_ImplSDL3_Shutdown();
}

void Sdl3Platform::NewFrame() {
    ImGui_ImplSDL3_NewFrame();
}

bool Sdl3Platform::ProcessEvent(void* event) {
    return ImGui_ImplSDL3_ProcessEvent(static_cast<SDL_Event*>(event));
}

void* Sdl3Platform::GetRequiredInstanceExtensions(uint32_t& count) {
    if (renderer_type_ == renderer::Type::Vulkan) {
        return const_cast<char**>(SDL_Vulkan_GetInstanceExtensions(&count));
    }
    count = 0;
    return nullptr;
}

bool Sdl3Platform::CreateSurface(void* instance, void* allocator, void* surface) {
    if (renderer_type_ == renderer::Type::Vulkan) {
        return SDL_Vulkan_CreateSurface(window_,
                                      static_cast<VkInstance>(instance),
                                      static_cast<const VkAllocationCallbacks*>(allocator),
                                      static_cast<VkSurfaceKHR*>(surface)) != 0;
    }
    return false;
}

void Sdl3Platform::MakeContextCurrent() {
    if (renderer_type_ == renderer::Type::OpenGL && gl_context_) {
        SDL_GL_MakeCurrent(window_, gl_context_);
    }
}

}  // namespace vkrt::platform