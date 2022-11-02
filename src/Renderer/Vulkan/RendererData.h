//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
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

        u32 queueFamilyIndex;

        RendererSpec rendererSpec;
        VkSurfaceKHR surface;

        SwapChainSpec swapchainSpec;
        Ref<Swapchain> swapchain;
        VkRenderPass renderPass;

        Ref<VulkanShader> defaultShader;
        Ref<VulkanFramebuffer> framebuffer;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        u32 currentFrameIndex;
        u32 maxFramesInFlight = 2;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        VkQueue presentQueue;
        VkQueue graphicsQueue;

        std::string shaderPath;
        std::string workingDir;

        bool framebufferResized;

    };
}