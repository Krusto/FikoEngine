//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include <lwlog.h>
#include <iostream>
#include "RendererAPI.h"
#include "Window.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"
#include "Vulkan/Device.h"
#include "Vulkan/Swapchain.h"
#include "Vulkan/ImageView.h"
#include "Vulkan/Image.h"
#include "Vulkan/RendererData.h"
#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/Renderpass.h"
#include "Vulkan/Memory.h"
#include "Vulkan/Framebuffer.h"
#include "Vulkan/Command.h"
#include "Vulkan/Synchronization.h"

namespace FikoEngine {
    inline RendererDataAPI s_RendererData;

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererData.workingDir = applicationSpec.WorkingDirectory;
        s_RendererData.instance = CreateInstance(&s_RendererData,applicationSpec);
        s_RendererData.physicalDevice = SelectPhysicalDevice(&s_RendererData);
        rendererSpec.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        s_RendererData.device = CreateDevice(&s_RendererData,rendererSpec.extensions);
        s_RendererData.surface = applicationSpec.window->CreateSurface(s_RendererData.instance);
        s_RendererData.framebufferSize = rendererSpec.SurfaceSize;

        s_RendererData.shaderPath = "assets/basic";
        SwapchainRecreate(&s_RendererData,rendererSpec.SurfaceSize,s_RendererData.shaderPath.c_str());

        s_RendererData.commandPool = CreateCommandPool(&s_RendererData);
        s_RendererData.commandBuffers = CreateCommandBuffers(&s_RendererData,s_RendererData.imageViews.size());

        s_RendererData.imageAvailableSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.renderFinishedSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.inFlightFences = CreateFences(&s_RendererData,s_RendererData.maxFramesInFlight);

        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.graphicsQueue);
        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.presentQueue);

        LOG("Renderer initialized!");

    }
    void RendererAPI::Draw() {

        WaitFence(&s_RendererData, s_RendererData.currentImageIndex);

        uint32_t imageIndex;
        VkResult result;

        result = SwapchainAcquireNextImage(&s_RendererData, imageIndex, s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.shaderPath.c_str());
        }


        ResetFence(&s_RendererData, s_RendererData.currentImageIndex);

        ResetCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);

        BeginCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);
        BeginRenderPass(&s_RendererData, s_RendererData.currentImageIndex);
        BindGraphicsPipeline(&s_RendererData, s_RendererData.currentImageIndex);
        GraphicsPipelineDraw(&s_RendererData, s_RendererData.currentImageIndex);
        EndRenderPass(&s_RendererData, s_RendererData.currentImageIndex);
        EndCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);

        QueueSubmit(&s_RendererData, s_RendererData.currentImageIndex);

        result = QueuePresent(&s_RendererData, imageIndex, s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || s_RendererData.framebufferResized) {
            SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.shaderPath.c_str());
            s_RendererData.framebufferResized = 0;
        }

        s_RendererData.currentImageIndex = (s_RendererData.currentImageIndex + 1) % s_RendererData.maxFramesInFlight;
    }
    void RendererAPI::Destroy(){
        vkDeviceWaitIdle(s_RendererData.device);

        for (u32 i = 0; i < s_RendererData.maxFramesInFlight; ++i) {
            vkDestroySemaphore(s_RendererData.device,s_RendererData.imageAvailableSemaphores[i],CreatePAllocator("Semaphore"));
            vkDestroySemaphore(s_RendererData.device,s_RendererData.renderFinishedSemaphores[i],CreatePAllocator("Semaphore"));
            vkDestroyFence(s_RendererData.device,s_RendererData.inFlightFences[i],CreatePAllocator("Fence"));
        }
        vkDestroyCommandPool(s_RendererData.device,s_RendererData.commandPool, CreatePAllocator("CommandPool"));
        SwapchainCleanup(&s_RendererData);
        vkDestroySurfaceKHR(s_RendererData.instance,s_RendererData.surface,CreatePAllocator("Surface"));
        vkDestroyDevice(s_RendererData.device,CreatePAllocator("Device"));
        DestroyDebugUtilsMessengerEXT(s_RendererData.instance,s_RendererData.debug,CreatePAllocator("Debug Util Messanger"));
        vkDestroyInstance(s_RendererData.instance,CreatePAllocator("Instance"));
    }

    void RendererAPI::ResizeFramebuffer(Extent2D size) {
//        SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.shaderPath.c_str());
        s_RendererData.framebufferResized = true;
        s_RendererData.framebufferSize = size;
    }

}