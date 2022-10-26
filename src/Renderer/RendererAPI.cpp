//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include "RendererAPI.h"
#include "Window.h"

#include "Vulkan/VulkanContext.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"
#include "Vulkan/Device.h"
#include "Vulkan/Swapchain.h"
#include "Vulkan/RendererData.h"
#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/Renderpass.h"
#include "Vulkan/Memory.h"
#include "Vulkan/Command.h"
#include "Vulkan/Synchronization.h"
#include "Vulkan/Queue.h"
#include "Renderer.h"

namespace FikoEngine {

    void RendererAPI::Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::Init(rendererSpec,applicationSpec);
                break;
            default:
                exit(-1);
                break;
        }

        LOG("Renderer initialized!");
    }
    void RendererAPI::Draw() {

        WaitFence(VulkanContext::s_RendererData.inFlightFences,VulkanContext::s_RendererData.currentImageIndex);

        uint32_t imageIndex;
        VkResult result;

        result = SwapchainAcquireNextImage(VulkanContext::s_RendererData.defaultShader->getSwapchain(),
                                           VulkanContext::s_RendererData.imageAvailableSemaphores[VulkanContext::s_RendererData.currentImageIndex],
                                           imageIndex,
                                           VulkanContext::s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            SwapchainRecreate(VulkanContext::s_RendererData.defaultShader->getSwapchain(),
                              VulkanContext::s_RendererData.physicalDevice,
                              VulkanContext::s_RendererData.device,
                              VulkanContext::s_RendererData.defaultShader->getSwapchain().FrameSize,
                              VulkanContext::s_RendererData.workingDir,
                              VulkanContext::s_RendererData.defaultShader->getSwapchain().);
            SwapchainRecreate(s_RendererData.swapchain,s_RendererData.physicalDevice,s_RendererData.device, s_RendererData.swapchain.FrameSize,s_RendererData.workingDir, s_RendererData.shaderPath);
        }


        ResetFence(&s_RendererData, s_RendererData.currentImageIndex);

        ResetCommandBuffer(s_RendererData.commandBuffers, s_RendererData.currentImageIndex);

        BeginCommandBuffer(s_RendererData.commandBuffers, s_RendererData.currentImageIndex);
        BeginRenderPass(s_RendererData.commandBuffers,s_RendererData.swapchain, s_RendererData.currentImageIndex);
        BindGraphicsPipeline(s_RendererData.commandBuffers,s_RendererData.swapchain, s_RendererData.currentImageIndex);
        GraphicsPipelineDraw(s_RendererData.commandBuffers, s_RendererData.currentImageIndex);
        EndRenderPass(s_RendererData.commandBuffers, s_RendererData.currentImageIndex);
        EndCommandBuffer(s_RendererData.commandBuffers, s_RendererData.currentImageIndex);

        QueueSubmit(&s_RendererData, s_RendererData.currentImageIndex);

        result = QueuePresent(&s_RendererData, imageIndex, s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || s_RendererData.framebufferResized) {
            SwapchainRecreate(s_RendererData.swapchain,s_RendererData.physicalDevice,s_RendererData.device, s_RendererData.swapchain.FrameSize,s_RendererData.workingDir, s_RendererData.shaderPath.c_str());
            s_RendererData.framebufferResized = 0;
        }

        s_RendererData.currentImageIndex = (s_RendererData.currentImageIndex + 1) % s_RendererData.maxFramesInFlight;
    }
    void RendererAPI::Destroy(){
        vkDeviceWaitIdle(s_RendererData.device);

        for (u32 i = 0; i < s_RendererData.maxFramesInFlight; ++i) {
            vkDestroySemaphore(s_RendererData.device,s_RendererData.imageAvailableSemaphores[i],nullptr);
            vkDestroySemaphore(s_RendererData.device,s_RendererData.renderFinishedSemaphores[i],nullptr);
            vkDestroyFence(s_RendererData.device,s_RendererData.inFlightFences[i],nullptr);
        }
        vkDestroyCommandPool(s_RendererData.device,s_RendererData.commandPool, nullptr);
        SwapchainCleanup(s_RendererData.device,s_RendererData.swapchain);
        vkDestroySurfaceKHR(s_RendererData.instance,s_RendererData.surface,nullptr);
        vkDestroyDevice(s_RendererData.device,nullptr);
        DestroyDebugUtilsMessengerEXT(s_RendererData.instance,s_RendererData.debug,nullptr);
        vkDestroyInstance(s_RendererData.instance,nullptr);
    }

    void RendererAPI::ResizeFramebuffer(ViewportSize size) {
//        SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.shaderPath.c_str());
        s_RendererData.framebufferResized = true;
        s_RendererData.swapchain.FrameSize = size;
    }

    void RendererAPI::ClearColor(glm::vec4 color) {
        //TODO
    }

    void RendererAPI::InitImGUI() {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::InitImGUI();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::SetActiveWindow(Window *window) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::s_RendererData.window = window->getHandle();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::AddShader(Ref<Shader> shader) {
        RendererAPI::s_Shaders.try_emplace(shader.Raw()->GetName(),shader);
    }

}