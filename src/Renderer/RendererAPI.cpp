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
    static QueueFamilyIndices s_RendererQueueFamilyIndices;

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererData.workingDir = applicationSpec.WorkingDirectory;
        s_RendererData.instance = CreateInstance(s_RendererData,applicationSpec);
        s_RendererData.physicalDevice = SelectPhysicalDevice(s_RendererData);
        rendererSpec.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        s_RendererData.device = CreateDevice(s_RendererData,rendererSpec.extensions);
        s_RendererData.surface = applicationSpec.window->CreateSurface(s_RendererData.instance);
        s_RendererData.swapchain = CreateSwapchain(s_RendererData,{rendererSpec.SurfaceWidth,rendererSpec.SurfaceHeight});
        s_RendererData.swapchainImages = GetSwapchainImages(s_RendererData);
        s_RendererData.imageViews = CreateImageViews(s_RendererData);
        s_RendererData.renderPass = CreateRenderPass(s_RendererData);
        s_RendererData.graphicsPipeline = CreateGraphicsPipeline(s_RendererData,"assets/basic");
        s_RendererData.swapChainFramebuffers = CreateFramebuffers(s_RendererData);
        s_RendererData.commandPool = CreateCommandPool(s_RendererData);
        s_RendererData.commandBuffers = CreateCommandBuffers(s_RendererData,s_RendererData.imageViews.size());

        s_RendererData.imageAvailableSemaphores = CreateSemaphores(s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.renderFinishedSemaphores = CreateSemaphores(s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.inFlightFences = CreateFences(s_RendererData,s_RendererData.maxFramesInFlight);

        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.graphicsQueue);
        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.presentQueue);

        LOG("Renderer initialized!");

    }
    void RendererAPI::Draw(){
/*        Wait for the previous frame to finish
        Acquire an image from the swap chain
        Record a command buffer which draws the scene onto that image
        Submit the recorded command buffer
        Present the swap chain image*/
        vkWaitForFences(s_RendererData.device, 1, &s_RendererData.inFlightFences[s_RendererData.currentImageIndex], VK_TRUE, UINT64_MAX);
        vkResetFences(s_RendererData.device, 1, &s_RendererData.inFlightFences[s_RendererData.currentImageIndex]);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(s_RendererData.device, s_RendererData.swapchain, UINT64_MAX, s_RendererData.imageAvailableSemaphores[s_RendererData.currentImageIndex], VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(s_RendererData.commandBuffers[s_RendererData.currentImageIndex], /*VkCommandBufferResetFlagBits*/ 0);

        BeginCommandBuffer(s_RendererData,s_RendererData.currentImageIndex);
        BeginRenderPass(s_RendererData,s_RendererData.currentImageIndex);
            vkCmdBindPipeline(s_RendererData.commandBuffers[s_RendererData.currentImageIndex],VK_PIPELINE_BIND_POINT_GRAPHICS,s_RendererData.graphicsPipeline);
            GraphicsPipelineDraw(s_RendererData,s_RendererData.currentImageIndex);
        EndRenderPass(s_RendererData,s_RendererData.currentImageIndex);
        EndCommandBuffer(s_RendererData,s_RendererData.currentImageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {s_RendererData.imageAvailableSemaphores[s_RendererData.currentImageIndex]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &s_RendererData.commandBuffers[s_RendererData.currentImageIndex];

        VkSemaphore signalSemaphores[] = {s_RendererData.renderFinishedSemaphores[s_RendererData.currentImageIndex]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(s_RendererData.graphicsQueue, 1, &submitInfo, s_RendererData.inFlightFences[s_RendererData.currentImageIndex]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {s_RendererData.swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(s_RendererData.presentQueue, &presentInfo);

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
        for (const auto &framebuffer: s_RendererData.swapChainFramebuffers)
            vkDestroyFramebuffer(s_RendererData.device,framebuffer,CreatePAllocator("Framebuffer"));
        vkDestroyPipeline(s_RendererData.device,s_RendererData.graphicsPipeline,CreatePAllocator("Graphics pipeline"));
        vkDestroyPipelineLayout(s_RendererData.device,s_RendererData.pipelineLayout,CreatePAllocator("Pipeline layout"));
        vkDestroyRenderPass(s_RendererData.device,s_RendererData.renderPass,CreatePAllocator("Pipeline layout"));
        for (const auto &view: s_RendererData.imageViews)
            vkDestroyImageView(s_RendererData.device,view,CreatePAllocator("Image View"));
        vkDestroySwapchainKHR(s_RendererData.device,s_RendererData.swapchain,CreatePAllocator("Swapchain"));
        vkDestroySurfaceKHR(s_RendererData.instance,s_RendererData.surface,CreatePAllocator("Surface"));
        vkDestroyDevice(s_RendererData.device,CreatePAllocator("Device"));
        DestroyDebugUtilsMessengerEXT(s_RendererData.instance,s_RendererData.debug,CreatePAllocator("Debug Util Messanger"));
        vkDestroyInstance(s_RendererData.instance,CreatePAllocator("Instance"));
    }

}