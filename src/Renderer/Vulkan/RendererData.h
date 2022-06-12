//
// Created by KSTOYAN2 on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../RendererSpec.h"
#include "SwapchainSpec.h"
#include "../../Core/Core.h"
namespace FikoEngine{
    struct RendererDataAPI{
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapchain;
        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> imageViews;
        RendererSpecAPI rendererSpec;
        SwapChainSpec swapChainSpec;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
        VkPipelineLayout pipelineLayout;
        std::string workingDir;
        VkShaderModule vertModule;
        VkShaderModule fragModule;
    };
    inline RendererDataAPI s_RendererData;
}