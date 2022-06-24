//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../RendererSpec.h"
#include "SwapchainSpec.h"
#include "../../Core/Core.h"
#include "Buffer.h"

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
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        u32 maxFramesInFlight = 2;
        VkQueue presentQueue;
        VkQueue graphicsQueue;
        std::vector<std::string> shaders;
        u32 selectedShaderID;
        std::string selectedShader;
        Extent2D framebufferSize;
        bool framebufferResized;
        Buffer vertexBuffer;
        Buffer indexBuffer;
        VkAllocationCallbacks* allocator;
    };
}