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

        void Begin();
        void End();

        ~VulkanCore();

    private:
        void mAcquireNextImage();

        VkResult mCreateSemaphores();

    private:
        FikoEngine::Window* mWindow;
        std::vector<VkPhysicalDevice> mPhysicalDevices;

        VkPhysicalDevice mPhysicalDevice;

        VkInstance mInstance;
        VkDevice mDevice;
        VkDebugReportCallbackEXT mDebugReportCallback;
        VkSurfaceKHR mSurface;
        uint32_t mQueueFamilyIndex;
        VkSwapchainKHR mSwapchain;
        VkCommandPool mCommandPool;


        std::vector<VkImage> mSwapchainImages;
        std::vector<VkImageView> mSwapchainImagesView;
        VkSurfaceFormatKHR mSurfaceFormat;
        VkSemaphore mWaitSemaphore;
        VkSemaphore mSignalSemaphore;
        VkRenderPass mRenderPass;
        uint32_t mSwapchainImageIndex;

        VkPipeline mGraphicsPipeline;

    };
}

#endif //FIKOENGINE_VULKANCORE_H
