#include "Swapchain.h"
#include "Queue.h"
#include "Memory.h"
#include "Image.h"
#include "ImageView.h"
#include "Renderpass.h"
#include "GraphicsPipeline.h"
#include "Framebuffer.h"
#include "../Vertex.h"

namespace FikoEngine {
    bool CheckDeviceExtensionSupport(RendererDataAPI*  rendererData, std::string_view extension) {
        uint32_t extensionCount{};
        vkEnumerateDeviceExtensionProperties(rendererData->physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(rendererData->physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        for (const auto &availableExtension: availableExtensions) {
            if (extension == availableExtension.extensionName)
                return true;
        }
        return false;
    }

    bool CheckSwapChainSupport(RendererDataAPI*  rendererData) {
        bool isExtensionPresent = CheckDeviceExtensionSupport(rendererData, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        if (!isExtensionPresent) {
            LOG_ERROR("VK_KHR_swapchain extension not supported!");
        }
        return isExtensionPresent;
    }

    SwapChainSupportDetails GetSwapchainSupportDetails(RendererDataAPI*  rendererData) {
        SwapChainSupportDetails details{};
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(rendererData->physicalDevice,rendererData->surface,&details.capabilities);

        u32 formatCount{};
        vkGetPhysicalDeviceSurfaceFormatsKHR(rendererData->physicalDevice,rendererData->surface,&formatCount,nullptr);
        if(formatCount > 0){
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(rendererData->physicalDevice,rendererData->surface,&formatCount,details.formats.data());
        }
        u32 presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(rendererData->physicalDevice, rendererData->surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(rendererData->physicalDevice, rendererData->surface, &presentModeCount, details.presentModes.data());
        }

        return details;

    }

    VkSurfaceFormatKHR ChooseSurfaceFormat(RendererDataAPI*  rendererData) {
        for (const auto& availableFormat : rendererData->swapChainSpec.details.formats)
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        return rendererData->swapChainSpec.details.formats[0];
    }

    VkPresentModeKHR ChoosePresentMode(RendererDataAPI*  rendererData) {
        for (const auto& availablePresentMode : rendererData->swapChainSpec.details.presentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D ChooseSwapExtent(RendererDataAPI*  rendererData,VkExtent2D windowExtent) {
        if (rendererData->swapChainSpec.details.capabilities.currentExtent.width != UINT32_MAX) {
            return rendererData->swapChainSpec.details.capabilities.currentExtent;
        } else {

            windowExtent.width = std::clamp(windowExtent.width,rendererData->swapChainSpec.details.capabilities.minImageExtent.width, rendererData->swapChainSpec.details.capabilities.maxImageExtent.width);
            windowExtent.height = std::clamp(windowExtent.height, rendererData->swapChainSpec.details.capabilities.minImageExtent.height, rendererData->swapChainSpec.details.capabilities.maxImageExtent.height);
            return windowExtent;
        }
    }

    VkSwapchainKHR CreateSwapchain(RendererDataAPI*  rendererData,Extent2D windowExtent) {
        rendererData->swapChainSpec.details = GetSwapchainSupportDetails(rendererData);
        rendererData->swapChainSpec.minImageCount = rendererData->swapChainSpec.details.capabilities.minImageCount;
        rendererData->swapChainSpec.imageFormat = ChooseSurfaceFormat(rendererData).format;
        rendererData->swapChainSpec.imageColorSpace = ChooseSurfaceFormat(rendererData).colorSpace;
        rendererData->swapChainSpec.imageExtent = ChooseSwapExtent(rendererData,{windowExtent.x,windowExtent.y});
        rendererData->swapChainSpec.imageArrayLayers = 1;
        rendererData->swapChainSpec.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        rendererData->swapChainSpec.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        rendererData->swapChainSpec.preTransform = rendererData->swapChainSpec.details.capabilities.currentTransform;
        rendererData->swapChainSpec.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        rendererData->swapChainSpec.presentMode = ChoosePresentMode(rendererData);
        rendererData->swapChainSpec.clipped = VK_TRUE;


        VkSwapchainKHR swapchain{};
        VkSwapchainCreateInfoKHR createInfo{.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};

        createInfo.surface = rendererData->surface;
        createInfo.minImageCount = rendererData->swapChainSpec.minImageCount;
        createInfo.imageFormat = rendererData->swapChainSpec.imageFormat;
        createInfo.imageColorSpace = rendererData->swapChainSpec.imageColorSpace;
        createInfo.imageExtent = rendererData->swapChainSpec.imageExtent;
        createInfo.imageArrayLayers = rendererData->swapChainSpec.imageArrayLayers;
        createInfo.imageUsage = rendererData->swapChainSpec.imageUsage;
        createInfo.imageSharingMode = rendererData->swapChainSpec.imageSharingMode;
        createInfo.queueFamilyIndexCount = 1; // Optional
        u32 index = SelectQueueFamily(rendererData);
        createInfo.pQueueFamilyIndices = &index; // Optional
        createInfo.preTransform = rendererData->swapChainSpec.details.capabilities.currentTransform;
        createInfo.compositeAlpha = rendererData->swapChainSpec.compositeAlpha;
        createInfo.presentMode = rendererData->swapChainSpec.presentMode;
        createInfo.clipped = rendererData->swapChainSpec.clipped;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VK_CHECK(vkCreateSwapchainKHR(rendererData->device,&createInfo,CreatePAllocator("Swapchain"),&swapchain));
        LOG_INFO("Swapchain created successfully!");
        return swapchain;
    }

    void SwapchainRecreate(RendererDataAPI*  rendererData,Extent2D size,const char* ShaderPath){
        vkDeviceWaitIdle(rendererData->device);

        SwapchainCleanup(rendererData);

        rendererData->swapchain = CreateSwapchain(rendererData,size);
        rendererData->swapchainImages = GetSwapchainImages(rendererData);
        rendererData->imageViews = CreateImageViews(rendererData);
        rendererData->renderPass = CreateRenderPass(rendererData);
        rendererData->graphicsPipeline = CreateGraphicsPipeline(rendererData,Vertex::GetBindingDescription(),Vertex::GetAttributeDescriptions(),ShaderPath);
        rendererData->swapChainFramebuffers = CreateFramebuffers(rendererData);

    }
    void SwapchainCleanup(RendererDataAPI*  rendererData){
        for (const auto &framebuffer: rendererData->swapChainFramebuffers)
            vkDestroyFramebuffer(rendererData->device,framebuffer,CreatePAllocator("Framebuffer"));
        vkDestroyPipeline(rendererData->device,rendererData->graphicsPipeline,CreatePAllocator("Graphics pipeline"));
        vkDestroyPipelineLayout(rendererData->device,rendererData->pipelineLayout,CreatePAllocator("Pipeline layout"));
        vkDestroyRenderPass(rendererData->device,rendererData->renderPass,CreatePAllocator("Pipeline layout"));
        for (const auto &view: rendererData->imageViews)
            vkDestroyImageView(rendererData->device,view,CreatePAllocator("Image View"));
        vkDestroySwapchainKHR(rendererData->device,rendererData->swapchain,CreatePAllocator("Swapchain"));
    }
    VkResult SwapchainAcquireNextImage(RendererDataAPI*  rendererData,u32& imageIndex,u32 commandBufferIndex){
        return vkAcquireNextImageKHR(rendererData->device,
                                       rendererData->swapchain,
                                       UINT64_MAX,
                                       rendererData->imageAvailableSemaphores[commandBufferIndex],
                                       VK_NULL_HANDLE,
                                       &imageIndex);

    }

}