//
// Created by Stoyanov, Krusto (K.S.) on 6/10/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include "SwapchainSpec.h"
#include "Renderer/Viewport.h"

namespace FikoEngine {

    class Swapchain{
    public:
        Swapchain() = default;
        Swapchain& operator=(Swapchain&) = default;



        u32 FramesCount;
        VkSwapchainKHR swapchain;
        std::vector<VkFramebuffer> Framebuffers;
        std::vector<VkImage> Images;
        std::vector<VkImageView> ImageViews;
        VkRenderPass Renderpass;
        ViewportSize FrameSize;
        SwapChainSpec SwapchainSpec;
        VkSurfaceKHR Surface;
        VkPipelineLayout PipelineLayout;
        VkPipeline GraphicsPipeline;

        u32 QueueFamilyIndex;

        operator VkSwapchainKHR(){
            return swapchain;
        }
    };

    bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::string_view extension);

    bool CheckSwapChainSupport(VkPhysicalDevice physicalDevice);

    SwapChainSupportDetails GetSwapchainSupportDetails(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface);

    VkSurfaceFormatKHR ChooseSurfaceFormat(SwapChainSpec& spec);

    VkPresentModeKHR ChoosePresentMode(SwapChainSpec& spec);

    VkExtent2D ChooseSwapExtent(SwapChainSpec& spec,VkExtent2D windowExtent);

    VkSwapchainKHR CreateSwapchain(VkPhysicalDevice physicalDevice,VkDevice device,SwapChainSpec& spec,VkSurfaceKHR surface,u32 queueFamilyIndex,ViewportSize windowExtent);

    VkResult SwapchainAcquireNextImage(VkDevice device,Swapchain& swapchain,VkSemaphore semaphore,u32& imageIndex,u32 commandBufferIndex);

    void SwapchainRecreate(Swapchain& swapchain,VkPhysicalDevice physicalDevice,VkDevice device,ViewportSize size,std::string_view workingDir,std::string_view shaderPath);

    void SwapchainCleanup(VkDevice device,Swapchain& swapchain);

    void BeginRenderPass(std::vector<VkCommandBuffer> commandBuffers,Swapchain& swapchain, u32 index);
    void EndRenderPass(std::vector<VkCommandBuffer> commandBuffers,u32 index);

    void BindGraphicsPipeline(std::vector<VkCommandBuffer> commandBuffers,Swapchain& swapchain,u32 imageIndex);
    void GraphicsPipelineDraw(std::vector<VkCommandBuffer> commandBuffers,u32 imageIndex);
}