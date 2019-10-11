
#include <vector>
#include "Swapchain.h"
#include "../VulkanUtilities.h"

std::pair<VkSwapchainKHR, VkSurfaceFormatKHR>
FikoEngine::VulkanRenderer::Swapchain::createSwapchain(VkPhysicalDevice physicalDevice,VkDevice device, VkSurfaceKHR surface,
                                                       uint32_t queueFamilyIndex) {

    auto result = std::pair<VkSwapchainKHR ,VkSurfaceFormatKHR >();

    std::vector<VkSurfaceFormatKHR>formatsKHR;
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
    formatsKHR.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formatsKHR.data());

    result.second = formatsKHR[0];

    VkSurfaceCapabilitiesKHR capabilitiesKHR;
    VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,surface, &capabilitiesKHR));

    VkBool32 supported;
    vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,queueFamilyIndex,surface,&supported);



    createInfo.setSwapchainCreateInfo(  VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
                                        surface,
                                        capabilitiesKHR.minImageCount,
                                        result.second.format,
                                        result.second.colorSpace,
                                        capabilitiesKHR.currentExtent,
                                        1,
                                        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                        VK_SHARING_MODE_EXCLUSIVE,
                                        1,
                                        &queueFamilyIndex,
                                        capabilitiesKHR.currentTransform,
                                        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                                        VK_PRESENT_MODE_FIFO_KHR,
                                        VK_TRUE,
                                        VK_NULL_HANDLE
    );

     VK_CHECK(vkCreateSwapchainKHR(device,createInfo.getSwapchainCreateInfo(),nullptr,&result.first),"Can not create SwapchainKHR!");

    return result;
}

std::vector<VkImage>
FikoEngine::VulkanRenderer::Swapchain::getSwapchainImages(VkDevice device, VkSwapchainKHR swapchain) {
    uint32_t count;
    std::vector<VkImage>images;

    VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain, &count, nullptr),"Can not get swapchain image count!");

    VK_CHECK((count >=2 )? VK_SUCCESS : VK_TIMEOUT,"Swap chain image count is not correct!");

    images.resize(count);
    VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain, &count, images.data()),"Can not get swapchain images!");

    return images;
}

std::vector<VkImageView>
FikoEngine::VulkanRenderer::Swapchain::getSwapchainImagesView(VkDevice device, std::vector<VkImage> swapchainImages,VkSurfaceFormatKHR surfaceFormat) {
    std::vector<VkImageView> swapchainImagesView(swapchainImages.size());
    for (uint32_t i = 0; i < swapchainImages.size(); ++i)
    {
        VkImageViewCreateInfo imageViewCreateInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
        imageViewCreateInfo.image = swapchainImages[i];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = surfaceFormat.format;
        imageViewCreateInfo.components = {VK_COMPONENT_SWIZZLE_R,VK_COMPONENT_SWIZZLE_G,VK_COMPONENT_SWIZZLE_B,VK_COMPONENT_SWIZZLE_A};
        imageViewCreateInfo.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT,0,1,0,1};

        VK_CHECK(vkCreateImageView(device, &imageViewCreateInfo, nullptr, &swapchainImagesView[i]),"Can not create image view with id:" + std::to_string(i)+" !");
    }
    return swapchainImagesView;
}
