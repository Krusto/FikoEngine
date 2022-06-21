//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../RendererSpec.h"
#include "SwapchainSpec.h"
#include "../../Core/Core.h"
namespace FikoEngine{
    struct RendererDataAPI{
        VkInstance instance;
        VkDebugUtilsMessengerEXT debug;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapchain;
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
    };
    inline RendererDataAPI s_RendererData;
}