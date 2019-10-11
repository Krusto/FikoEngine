//
// Created by krusto on 9/24/19.
//

#ifndef FIKOENGINE_SWAPCHAIN_H
#define FIKOENGINE_SWAPCHAIN_H

#include <vulkan/vulkan.h>
#include <utility>

namespace FikoEngine::VulkanRenderer {
    class Swapchain {
    public:
        static std::pair<VkSwapchainKHR ,VkSurfaceFormatKHR > createSwapchain(VkPhysicalDevice physicalDevice,VkDevice device, VkSurfaceKHR surface,uint32_t queueFamilyIndex);
        static std::vector<VkImage> getSwapchainImages(VkDevice device,VkSwapchainKHR swapchain);
        static std::vector<VkImageView> getSwapchainImagesView(VkDevice device,std::vector<VkImage> swapchainImages,VkSurfaceFormatKHR surfaceFormat);
    };
}

#endif //FIKOENGINE_SWAPCHAIN_H
