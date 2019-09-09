//
// Created by krusto on 31.08.19 г..
//

#ifndef FIKOENGINE_VULKANCORE_H
#define FIKOENGINE_VULKANCORE_H

#include <iostream>
#include <vulkan/vulkan.h>
#include "VulkanCreateInfos.h"
#include "../../../Window.h"

namespace FikoEngine::VulkanRenderer {
    class VulkanCore {
    public:
        VulkanCore() = default;

        void Init(FikoEngine::Window window);
        VkResult mCreateRenderpass();

        ~VulkanCore();

    private:

        VulkanCreateInfos createInfo;

        VkResult mCreateInstance();

        VkResult mSelectPhysicalDevice(VkPhysicalDeviceType physicalDeviceType);

        VkResult mSelectQueueFamilyIndex();

        VkResult mCreateDevice();

        VkResult mCreateDebugCallback();

        VkResult mGetSurface();

        VkResult mCreateSwapchainKHR();

        VkResult mCreateCommandPool();

        VkResult mAllocateCommandBuffers();

        VkResult mGetSwapchainImages();

        VkResult mGetSwapchainImagesView();

        VkResult mCreateSemaphores();

    private:
        FikoEngine::Window* mWindow;
        VkPhysicalDevice mPhysicalDevice;
        VkInstance mInstance;
        VkDevice mDevice;
        VkDebugReportCallbackEXT mDebugReportCallback;
        VkSurfaceKHR mSurface;
        uint32_t mQueueFamilyIndex;
        VkSwapchainKHR mSwapchain;
        VkCommandPool mCommandPool;
        std::vector<VkCommandBuffer> mCommandBuffers;
        std::vector<VkImage> mSwapchainImages;
        std::vector<VkImageView> mSwapchainImagesView;
        VkSurfaceFormatKHR mSurfaceFormat;
        VkSemaphore mWaitSemaphore;
        VkSemaphore mSignalSemaphore;
        VkRenderPass mRenderPass;
    };
}

#endif //FIKOENGINE_VULKANCORE_H
