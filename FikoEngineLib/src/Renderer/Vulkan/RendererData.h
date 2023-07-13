//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include <Renderer/Renderer.h>
#include <Renderer/RendererSpec.h>
#include "Renderer/Shader.h"
#include <Renderer/Vulkan/SwapchainSpec.h>
#include <Renderer/Vulkan/Swapchain.h>
#include <Renderer/Vulkan/VulkanShader.h>
#include <Renderer/Vulkan/Framebuffer.h>

namespace FikoEngine{
    struct RendererDataAPI{
        GLFWwindow* window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debug;
        VkPhysicalDevice physicalDevice;
        VkDevice device;

        uint32_t queueFamilyIndex;

        RendererSpec rendererSpec;
        VkSurfaceKHR surface;

        SwapChainSpec swapchainSpec;
        Ref<Swapchain> swapchain;
        VkRenderPass renderPass;

        Ref<Shader> currentShader;
        Ref<VulkanFramebuffer> framebuffer;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentFrameIndex;
        uint32_t currentImageIndex;
        uint32_t maxFramesInFlight = 2;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        VkQueue presentQueue;
        VkQueue graphicsQueue;

        std::string shaderPath;
        std::string workingDir;

        bool framebufferResized;

        VkDescriptorSetLayout descriptorSetLayout;
    };
}