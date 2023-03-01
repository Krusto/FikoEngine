//
// Created by Krusto on 21-Oct-22.
//

#include "VulkanRenderer.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "Command.h"
#include "Synchronization.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include "Renderpass.h"
#include "Application/Application.h"
#include "Queue.h"

namespace FikoEngine{

    void VulkanRenderer::Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererData.workingDir = applicationSpec.WorkingDirectory;
        s_RendererData.instance = CreateInstance(&s_RendererData,applicationSpec);
        s_RendererData.physicalDevice = SelectPhysicalDevice(&s_RendererData);
        s_RendererData.window = Application::Get().WindowHandle()->GetHandle();

        rendererSpec.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        s_RendererData.device = CreateDevice(s_RendererData.physicalDevice,s_RendererData.queueFamilyIndex,rendererSpec.extensions);

        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.graphicsQueue);
        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.presentQueue);

        s_RendererData.surface = Application::Get().WindowHandle()->CreateSurface(s_RendererData.instance);

        s_RendererData.commandPool = CreateCommandPool(s_RendererData.device,
                                                       s_RendererData.queueFamilyIndex);
        s_RendererData.commandBuffers = CreateCommandBuffers(s_RendererData.device,
                                                             s_RendererData.commandPool,2);

        s_RendererData.swapchain = Ref<Swapchain>::Create();
        s_RendererData.renderPass = CreateRenderPass(VulkanRenderer::s_RendererData.swapchain->GetSwapchainSpec());

        s_RendererData.imageAvailableSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.renderFinishedSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.inFlightFences = CreateFences(&s_RendererData,s_RendererData.maxFramesInFlight);

        LOG("Renderer initialized!");

    }
    void VulkanRenderer::InitImGUI() {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        //io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.TTF", 16);

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        //style.WindowPadding = ImVec2(0,0);
        style.WindowRounding = 0.0f;
        style.FramePadding = ImVec2(5, 5);
        style.FrameRounding = 0.0f;
        style.ItemSpacing = ImVec2(12, 8);
        style.ItemInnerSpacing = ImVec2(8, 6);
        style.IndentSpacing = 25.0f;
        style.ScrollbarSize = 15.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabMinSize = 5.0f;
        style.GrabRounding = 0.0f;


        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

        // Headers
        colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Resize Grip
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);

        // Scrollbar
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.0f);

        // Check Mark
        colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);

        // Slider
        colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 0.7f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForVulkan(GraphicsContext::s_Context->window, true);

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = s_RendererData.instance;
        init_info.PhysicalDevice = s_RendererData.physicalDevice;
        init_info.Device = s_RendererData.device;
        init_info.QueueFamily = s_RendererData.queueFamilyIndex;
        init_info.Queue = s_RendererData.graphicsQueue;
        init_info.PipelineCache = NULL;
        init_info.DescriptorPool = NULL;
        init_info.Subpass = 0;
        init_info.MinImageCount = s_RendererData.swapchain->FramesCount;
        init_info.ImageCount = s_RendererData.swapchain->FramesCount;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = nullptr;
        init_info.CheckVkResultFn = VK_CHECK;
        ImGui_ImplVulkan_Init(&init_info, s_RendererData.renderPass);

    }

    void VulkanRenderer::BeginFrame(){
        WaitFence(VulkanRenderer::s_RendererData.inFlightFences,VulkanRenderer::s_RendererData.currentFrameIndex);

        VkResult result = SwapchainAcquireNextImage(VulkanRenderer::s_RendererData.swapchain,
                                                    VulkanRenderer::s_RendererData.imageAvailableSemaphores[VulkanRenderer::s_RendererData.currentFrameIndex],
                                                    VulkanRenderer::s_RendererData.currentImageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            uint32_t width,height;
            glfwGetWindowSize(VulkanRenderer::s_RendererData.window,(int*)&width,(int*)&height);

        }else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }
    }
    void VulkanRenderer::EndFrame() {
        ResetFence(VulkanRenderer::s_RendererData.inFlightFences, VulkanRenderer::s_RendererData.currentFrameIndex);

        QueueSubmit(VulkanRenderer::s_RendererData.graphicsQueue,
                    VulkanRenderer::s_RendererData.imageAvailableSemaphores,
                    VulkanRenderer::s_RendererData.renderFinishedSemaphores,
                    VulkanRenderer::s_RendererData.inFlightFences,
                    VulkanRenderer::s_RendererData.currentFrameIndex);

        VkResult result = QueuePresent(VulkanRenderer::s_RendererData.graphicsQueue,
                              VulkanRenderer::s_RendererData.swapchain,
                              VulkanRenderer::s_RendererData.renderFinishedSemaphores,
                              VulkanRenderer::s_RendererData.inFlightFences,
                              VulkanRenderer::s_RendererData.currentImageIndex,
                              VulkanRenderer::s_RendererData.currentFrameIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || VulkanRenderer::s_RendererData.framebufferResized) {
            uint32_t width,height;
            glfwGetWindowSize(VulkanRenderer::s_RendererData.window,(int*)&width,(int*)&height);
        }

        VulkanRenderer::s_RendererData.currentFrameIndex = (VulkanRenderer::s_RendererData.currentFrameIndex + 1) % VulkanRenderer::s_RendererData.maxFramesInFlight;
    }
    void VulkanRenderer::DrawIndexed(Ref<VertexArray>& va) {
        BeginCommandBuffer(VulkanRenderer::s_RendererData.commandBuffers,
                               VulkanRenderer::s_RendererData.currentFrameIndex);

        auto &swapchain = VulkanRenderer::s_RendererData.swapchain;

        BeginRenderPass(VulkanRenderer::s_RendererData.commandBuffers,
                            swapchain,
                            imageIndex);

        BindGraphicsPipeline(VulkanRenderer::s_RendererData.commandBuffers,
                             VulkanRenderer::s_RendererData.currentShader,
                             VulkanRenderer::s_RendererData.currentFrameIndex);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapchain->GetSwapchainSpec().frameSize.width;
        viewport.height = (float) swapchain->GetSwapchainSpec().frameSize.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(
                VulkanRenderer::s_RendererData.commandBuffers[VulkanRenderer::s_RendererData.currentFrameIndex],
                0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapchain->GetSwapchainSpec().imageExtent;
        vkCmdSetScissor(
                VulkanRenderer::s_RendererData.commandBuffers[VulkanRenderer::s_RendererData.currentFrameIndex],
                0, 1, &scissor);
        va->Bind();
        vkCmdDrawIndexed(VulkanRenderer::s_RendererData.commandBuffers[VulkanRenderer::s_RendererData.currentFrameIndex],
                         va->IndexCount,1,0,0,0);

       // GraphicsPipelineDraw(VulkanRenderer::s_RendererData.commandBuffers,
       //                      VulkanRenderer::s_RendererData.currentFrameIndex);

        EndRenderPass(VulkanRenderer::s_RendererData.commandBuffers,
                      VulkanRenderer::s_RendererData.currentFrameIndex);

        EndCommandBuffer(VulkanRenderer::s_RendererData.commandBuffers,
                         VulkanRenderer::s_RendererData.currentFrameIndex);
    }

    void VulkanRenderer::Shutdown() {
        vkDeviceWaitIdle(VulkanRenderer::s_RendererData.device);

        for (u32 i = 0; i < VulkanRenderer::s_RendererData.maxFramesInFlight; ++i) {
            vkDestroySemaphore(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.imageAvailableSemaphores[i],nullptr);
            vkDestroySemaphore(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.renderFinishedSemaphores[i],nullptr);
            vkDestroyFence(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.inFlightFences[i],nullptr);
        }
        vkDestroyCommandPool(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.commandPool, nullptr);

        VulkanRenderer::s_RendererData.swapchain->Cleanup();

        vkDestroySurfaceKHR(VulkanRenderer::s_RendererData.instance,VulkanRenderer::s_RendererData.surface,nullptr);
        vkDestroyDevice(VulkanRenderer::s_RendererData.device,nullptr);
        DestroyDebugUtilsMessengerEXT(VulkanRenderer::s_RendererData.instance,VulkanRenderer::s_RendererData.debug,nullptr);
        vkDestroyInstance(VulkanRenderer::s_RendererData.instance,nullptr);
    }
}