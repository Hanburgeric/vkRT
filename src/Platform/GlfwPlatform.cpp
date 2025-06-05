#include "GlfwPlatform.h"

// STL
#include <iostream>

// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Vulkan (for types in CreateSurface)
#include <vulkan/vulkan.h>

// ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace vkrt::platform {

GlfwPlatform::GlfwPlatform()
    : window_(nullptr)
    , renderer_type_(renderer::Type::Vulkan)
    , width_(1280)
    , height_(720) {
}

GlfwPlatform::~GlfwPlatform() {
    Shutdown();
}

bool GlfwPlatform::Initialize(const PlatformCreateInfo& info) {
    renderer_type_ = info.renderer_type;
    width_ = info.window_width;
    height_ = info.window_height;

    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit()) {
        return false;
    }

    if (renderer_type_ == renderer::Type::Vulkan) {
        // Check for Vulkan support
        if (!glfwVulkanSupported()) {
            std::cerr << "GLFW: Vulkan Not Supported" << std::endl;
            return false;
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    } else if (renderer_type_ == renderer::Type::OpenGL) {
        // Decide GL+GLSL versions
#if defined(__APPLE__)
        // GL 3.2 + GLSL 150
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
        // GL 3.0 + GLSL 130
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
    }

    // Create window
    window_ = glfwCreateWindow(width_, height_, info.window_title, nullptr, nullptr);
    if (!window_) {
        return false;
    }

    if (renderer_type_ == renderer::Type::OpenGL) {
        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1); // Enable vsync
    }

    return true;
}

void GlfwPlatform::Shutdown() {
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}

bool GlfwPlatform::ShouldClose() const {
    return window_ && glfwWindowShouldClose(window_);
}

void GlfwPlatform::PollEvents() {
    glfwPollEvents();

    if (window_ && glfwGetWindowAttrib(window_, GLFW_ICONIFIED) != 0) {
        ImGui_ImplGlfw_Sleep(10);
    }
}

void GlfwPlatform::SwapBuffers() {
    if (renderer_type_ == renderer::Type::OpenGL && window_) {
        glfwSwapBuffers(window_);
    }
}

WindowInfo GlfwPlatform::GetWindowInfo() const {
    WindowInfo info;
    info.window = window_;
    info.context = nullptr;  // GLFW manages OpenGL context internally
    info.width = width_;
    info.height = height_;
    return info;
}

void GlfwPlatform::GetFramebufferSize(int& width, int& height) const {
    if (window_) {
        glfwGetFramebufferSize(window_, &width, &height);
    }
}

bool GlfwPlatform::InitializeImGui() {
    if (renderer_type_ == renderer::Type::OpenGL) {
        return ImGui_ImplGlfw_InitForOpenGL(window_, true);
    } else if (renderer_type_ == renderer::Type::Vulkan) {
        return ImGui_ImplGlfw_InitForVulkan(window_, true);
    }
    return false;
}

void GlfwPlatform::ShutdownImGui() {
    ImGui_ImplGlfw_Shutdown();
}

void GlfwPlatform::NewFrame() {
    ImGui_ImplGlfw_NewFrame();
}

bool GlfwPlatform::ProcessEvent(void* event) {
    // GLFW processes events automatically in glfwPollEvents()
    return false;
}

void* GlfwPlatform::GetRequiredInstanceExtensions(uint32_t& count) {
    if (renderer_type_ == renderer::Type::Vulkan) {
        return const_cast<char**>(glfwGetRequiredInstanceExtensions(&count));
    }
    count = 0;
    return nullptr;
}

bool GlfwPlatform::CreateSurface(void* instance, void* allocator, void* surface) {
    if (renderer_type_ == renderer::Type::Vulkan && window_) {
        VkResult result = glfwCreateWindowSurface(
            static_cast<VkInstance>(instance),
            window_,
            static_cast<const VkAllocationCallbacks*>(allocator),
            static_cast<VkSurfaceKHR*>(surface)
        );
        return result == VK_SUCCESS;
    }
    return false;
}

void GlfwPlatform::MakeContextCurrent() {
    if (renderer_type_ == renderer::Type::OpenGL && window_) {
        glfwMakeContextCurrent(window_);
    }
}

void GlfwPlatform::ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

}  // namespace vkrt::platform