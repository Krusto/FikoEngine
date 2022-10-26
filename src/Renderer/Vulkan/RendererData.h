//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../RendererSpec.h"
#include "SwapchainSpec.h"
#include "../../Core/Core.h"
#include "Swapchain.h"
#include "GLFW/glfw3.h"
#include "Renderer/Shader.h"
#include "VulkanShader.h"
#include "Renderer/Renderer.h"

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

        Ref<VulkanShader> imguiShader;
        Ref<VulkanShader> defaultShader;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        u32 currentImageIndex;
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