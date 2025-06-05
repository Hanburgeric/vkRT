#include "VulkanRenderer.h"

// STL
#include <iostream>
#include <cstdlib>

// ImGui
#include "imgui.h"
#include "imgui_impl_vulkan.h"

// src
#include "../Platform/Platform.h"

namespace vkrt::renderer {

VulkanRenderer::VulkanRenderer()
    : platform_(nullptr)
    , allocator_(nullptr)
    , instance_(VK_NULL_HANDLE)
    , physical_device_(VK_NULL_HANDLE)
    , device_(VK_NULL_HANDLE)
    , queue_family_(static_cast<uint32_t>(-1))
    , queue_(VK_NULL_HANDLE)
    , pipeline_cache_(VK_NULL_HANDLE)
    , descriptor_pool_(VK_NULL_HANDLE)
    , main_window_data_{}
    , min_image_count_(2)
    , swap_chain_rebuild_(false)
    , width_(1280)
    , height_(720) {

    clear_value_.color.float32[0] = 0.45f;
    clear_value_.color.float32[1] = 0.55f;
    clear_value_.color.float32[2] = 0.60f;
    clear_value_.color.float32[3] = 1.00f;
}

VulkanRenderer::~VulkanRenderer() {
    Shutdown();
}

bool VulkanRenderer::Initialize(const RendererCreateInfo& info) {
    platform_ = info.platform;
    width_ = info.width;
    height_ = info.height;

    if (!platform_) {
        std::cerr << "Vulkan Renderer: Platform is null" << std::endl;
        return false;
    }

    if (!SetupVulkan()) {
        std::cerr << "Failed to setup Vulkan" << std::endl;
        return false;
    }

    if (!SetupVulkanWindow(width_, height_)) {
        std::cerr << "Failed to setup Vulkan window" << std::endl;
        return false;
    }

    return true;
}

void VulkanRenderer::Shutdown() {
    // Wait for device to be idle before any cleanup
    if (device_ != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(device_);
    }

    // Clean up in proper order
    CleanupVulkanWindow();
    CleanupVulkan();

    platform_ = nullptr;
}

void VulkanRenderer::NewFrame() {
    // Handle window resize
    int fb_width, fb_height;
    platform_->GetFramebufferSize(fb_width, fb_height);

    if (fb_width > 0 && fb_height > 0 &&
        (swap_chain_rebuild_ || main_window_data_.Width != fb_width || main_window_data_.Height != fb_height)) {
        ImGui_ImplVulkan_SetMinImageCount(min_image_count_);
        ImGui_ImplVulkanH_CreateOrResizeWindow(instance_, physical_device_, device_,
                                               &main_window_data_, queue_family_,
                                               allocator_, fb_width, fb_height, min_image_count_);
        main_window_data_.FrameIndex = 0;
        swap_chain_rebuild_ = false;
        width_ = fb_width;
        height_ = fb_height;
    }

    // Call ImGui Vulkan NewFrame
    ImGui_ImplVulkan_NewFrame();
}

void VulkanRenderer::RenderFrame(ImDrawData* draw_data) {
    if (!draw_data) return;

    const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
    if (!is_minimized) {
        main_window_data_.ClearValue = clear_value_;
        FrameRender(draw_data);
        FramePresent();
    }
}

void VulkanRenderer::Present() {
    // Present is handled in FramePresent()
}

void VulkanRenderer::OnResize(int width, int height) {
    width_ = width;
    height_ = height;
    swap_chain_rebuild_ = true;
}

void VulkanRenderer::SetClearColor(float r, float g, float b, float a) {
    clear_value_.color.float32[0] = r * a;
    clear_value_.color.float32[1] = g * a;
    clear_value_.color.float32[2] = b * a;
    clear_value_.color.float32[3] = a;
}

bool VulkanRenderer::InitializeImGui() {
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = instance_;
    init_info.PhysicalDevice = physical_device_;
    init_info.Device = device_;
    init_info.QueueFamily = queue_family_;
    init_info.Queue = queue_;
    init_info.PipelineCache = pipeline_cache_;
    init_info.DescriptorPool = descriptor_pool_;
    init_info.RenderPass = main_window_data_.RenderPass;
    init_info.Subpass = 0;
    init_info.MinImageCount = min_image_count_;
    init_info.ImageCount = main_window_data_.ImageCount;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator = allocator_;
    init_info.CheckVkResultFn = CheckVkResult;

    if (!ImGui_ImplVulkan_Init(&init_info)) {
        return false;
    }

    // Upload fonts - use the newer API
    if (!ImGui_ImplVulkan_CreateFontsTexture()) {
        std::cerr << "Failed to create fonts texture" << std::endl;
        return false;
    }

    return true;
}

void VulkanRenderer::ShutdownImGui() {
    if (device_ != VK_NULL_HANDLE) {
        ImGui_ImplVulkan_DestroyFontsTexture();
        ImGui_ImplVulkan_Shutdown();
    }
}

bool VulkanRenderer::SetupVulkan() {
    // Get required extensions from platform
    uint32_t extensions_count = 0;
    const char** extensions = static_cast<const char**>(platform_->GetRequiredInstanceExtensions(extensions_count));

    if (!extensions || extensions_count == 0) {
        std::cerr << "Failed to get required Vulkan extensions" << std::endl;
        return false;
    }

    // Create Vulkan Instance
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.enabledExtensionCount = extensions_count;
    create_info.ppEnabledExtensionNames = extensions;

    VkResult err = vkCreateInstance(&create_info, allocator_, &instance_);
    CheckVkResult(err);

    // Select Physical Device (GPU)
    physical_device_ = ImGui_ImplVulkanH_SelectPhysicalDevice(instance_);
    if (physical_device_ == VK_NULL_HANDLE) {
        std::cerr << "Failed to select physical device" << std::endl;
        return false;
    }

    // Select graphics queue family
    queue_family_ = ImGui_ImplVulkanH_SelectQueueFamilyIndex(physical_device_);
    if (queue_family_ == static_cast<uint32_t>(-1)) {
        std::cerr << "Failed to select queue family" << std::endl;
        return false;
    }

    // Create Logical Device
    const char* device_extensions[] = { "VK_KHR_swapchain" };
    const float queue_priority[] = { 1.0f };

    VkDeviceQueueCreateInfo queue_info[1] = {};
    queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info[0].queueFamilyIndex = queue_family_;
    queue_info[0].queueCount = 1;
    queue_info[0].pQueuePriorities = queue_priority;

    VkDeviceCreateInfo device_create_info = {};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
    device_create_info.pQueueCreateInfos = queue_info;
    device_create_info.enabledExtensionCount = sizeof(device_extensions) / sizeof(device_extensions[0]);
    device_create_info.ppEnabledExtensionNames = device_extensions;

    err = vkCreateDevice(physical_device_, &device_create_info, allocator_, &device_);
    CheckVkResult(err);

    vkGetDeviceQueue(device_, queue_family_, 0, &queue_);

    // Create Descriptor Pool
    VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
    };
    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 1000;
    pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);
    pool_info.pPoolSizes = pool_sizes;

    err = vkCreateDescriptorPool(device_, &pool_info, allocator_, &descriptor_pool_);
    CheckVkResult(err);

    return true;
}

bool VulkanRenderer::SetupVulkanWindow(int width, int height) {
    // Create surface
    VkSurfaceKHR surface;
    if (!platform_->CreateSurface(instance_, allocator_, &surface)) {
        std::cerr << "Failed to create Vulkan surface" << std::endl;
        return false;
    }

    main_window_data_.Surface = surface;

    // Check for WSI support
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device_, queue_family_, surface, &res);
    if (res != VK_TRUE) {
        std::cerr << "Error: no WSI support on physical device" << std::endl;
        return false;
    }

    // Select Surface Format
    const VkFormat requestSurfaceImageFormat[] = {
        VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM
    };
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    main_window_data_.SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(
        physical_device_, surface, requestSurfaceImageFormat,
        sizeof(requestSurfaceImageFormat) / sizeof(requestSurfaceImageFormat[0]),
        requestSurfaceColorSpace);

    // Select Present Mode
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
    main_window_data_.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(
        physical_device_, surface, &present_modes[0],
        sizeof(present_modes) / sizeof(present_modes[0]));

    // Create SwapChain, RenderPass, Framebuffer, etc.
    ImGui_ImplVulkanH_CreateOrResizeWindow(instance_, physical_device_, device_,
                                           &main_window_data_, queue_family_,
                                           allocator_, width, height, min_image_count_);

    return true;
}

void VulkanRenderer::CleanupVulkan() {
    // Don't call vkDeviceWaitIdle here since it was already called in Shutdown()

    if (descriptor_pool_ != VK_NULL_HANDLE && device_ != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(device_, descriptor_pool_, allocator_);
        descriptor_pool_ = VK_NULL_HANDLE;
    }

    if (device_ != VK_NULL_HANDLE) {
        vkDestroyDevice(device_, allocator_);
        device_ = VK_NULL_HANDLE;
    }

    if (instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(instance_, allocator_);
        instance_ = VK_NULL_HANDLE;
    }
}

void VulkanRenderer::CleanupVulkanWindow() {
    if (device_ != VK_NULL_HANDLE) {
        ImGui_ImplVulkanH_DestroyWindow(instance_, device_, &main_window_data_, allocator_);
    }
}

void VulkanRenderer::FrameRender(ImDrawData* draw_data) {
    ImGui_ImplVulkanH_Window* wd = &main_window_data_;

    VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;

    VkResult err = vkAcquireNextImageKHR(device_, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
        swap_chain_rebuild_ = true;
        return;
    }
    CheckVkResult(err);

    ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
    {
        err = vkWaitForFences(device_, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
        CheckVkResult(err);

        err = vkResetFences(device_, 1, &fd->Fence);
        CheckVkResult(err);
    }
    {
        err = vkResetCommandPool(device_, fd->CommandPool, 0);
        CheckVkResult(err);

        VkCommandBufferBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
        CheckVkResult(err);
    }
    {
        VkRenderPassBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        info.renderPass = wd->RenderPass;
        info.framebuffer = fd->Framebuffer;
        info.renderArea.extent.width = wd->Width;
        info.renderArea.extent.height = wd->Height;
        info.clearValueCount = 1;
        info.pClearValues = &wd->ClearValue;
        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);
    {
        VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        VkSubmitInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &image_acquired_semaphore;
        info.pWaitDstStageMask = &wait_stage;
        info.commandBufferCount = 1;
        info.pCommandBuffers = &fd->CommandBuffer;
        info.signalSemaphoreCount = 1;
        info.pSignalSemaphores = &render_complete_semaphore;

        err = vkEndCommandBuffer(fd->CommandBuffer);
        CheckVkResult(err);
        err = vkQueueSubmit(queue_, 1, &info, fd->Fence);
        CheckVkResult(err);
    }
}

void VulkanRenderer::FramePresent() {
    if (swap_chain_rebuild_) return;

    ImGui_ImplVulkanH_Window* wd = &main_window_data_;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;

    VkPresentInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &render_complete_semaphore;
    info.swapchainCount = 1;
    info.pSwapchains = &wd->Swapchain;
    info.pImageIndices = &wd->FrameIndex;

    VkResult err = vkQueuePresentKHR(queue_, &info);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
        swap_chain_rebuild_ = true;
        return;
    }
    CheckVkResult(err);

    wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->SemaphoreCount;
}

void VulkanRenderer::CheckVkResult(VkResult err) {
    if (err == VK_SUCCESS) return;
    std::cerr << "[vulkan] Error: VkResult = " << err << std::endl;
    if (err < 0) {
        std::abort();
    }
}

}  // namespace vkrt::renderer