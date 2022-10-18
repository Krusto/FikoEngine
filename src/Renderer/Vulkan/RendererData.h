//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../RendererSpec.h"
#include "SwapchainSpec.h"
#include "../../Core/Core.h"
#include "Swapchain.h"

namespace FikoEngine{
    struct RendererDataAPI{
        VkInstance instance;
        VkDebugUtilsMessengerEXT debug;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkSurfaceKHR surface;
        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> imageViews;
        u32 queueFamilyIndex;
        RendererSpecAPI rendererSpec;
        SwapChainSpec swapChainSpec;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
        VkPipelineLayout pipelineLayout;
        std::string workingDir;
        VkShaderModule vertModule;
        VkShaderModule fragModule;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        u32 currentImageIndex;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        u32 maxFramesInFlight = 2;
        VkQueue presentQueue;
        VkQueue graphicsQueue;
        std::string shaderPath;
        Extent2D framebufferSize;
        bool framebufferResized;

        Swapchain swapchain;
    };
    inline RendererDataAPI s_RendererData;
}