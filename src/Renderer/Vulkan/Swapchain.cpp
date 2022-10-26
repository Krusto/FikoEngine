#include "Swapchain.h"
#include "Queue.h"
#include "Memory.h"
#include "Image.h"
#include "ImageView.h"
#include "Renderpass.h"
#include "GraphicsPipeline.h"
#include "Framebuffer.h"
#include "../Vertex.h"
#include "VulkanContext.h"

namespace FikoEngine {
    bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::string_view extension) {
        uint32_t extensionCount{};
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        for (const auto &availableExtension: availableExtensions) {
            if (extension == availableExtension.extensionName)
                return true;
        }
        return false;
    }

    bool CheckSwapChainSupport(VkPhysicalDevice physicalDevice) {
        bool isExtensionPresent = CheckDeviceExtensionSupport(physicalDevice, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        if (!isExtensionPresent) {
            LOG_ERROR("VK_KHR_swapchain extension not supported!");
        }
        return isExtensionPresent;
    }

    SwapChainSupportDetails GetSwapchainSupportDetails(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface) {
        SwapChainSupportDetails details{};
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,surface,&details.capabilities);

        u32 formatCount{};
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,nullptr);
        if(formatCount > 0){
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,details.formats.data());
        }
        u32 presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
        }
        
        if (details.capabilities.minImageCount < 2)
            details.capabilities.minImageCount = 2;

        return details;

    }

    VkSurfaceFormatKHR ChooseSurfaceFormat(SwapChainSpec& spec) {
        for (const auto& availableFormat : spec.details.formats)
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        return spec.details.formats[0];
    }

    VkPresentModeKHR ChoosePresentMode(SwapChainSpec& spec) {
        for (const auto& availablePresentMode : spec.details.presentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D ChooseSwapExtent(SwapChainSpec& spec,VkExtent2D windowExtent) {
        if (spec.details.capabilities.currentExtent.width != UINT32_MAX) {
            return spec.details.capabilities.currentExtent;
        } else {

            windowExtent.width = std::clamp(windowExtent.width,spec.details.capabilities.minImageExtent.width, spec.details.capabilities.maxImageExtent.width);
            windowExtent.height = std::clamp(windowExtent.height, spec.details.capabilities.minImageExtent.height, spec.details.capabilities.maxImageExtent.height);
            return windowExtent;
        }
    }

    VkSwapchainKHR CreateSwapchain(VkPhysicalDevice physicalDevice,VkDevice device,SwapChainSpec& spec,VkSurfaceKHR surface,u32 queueFamilyIndex,ViewportSize windowExtent) {

        spec.details = GetSwapchainSupportDetails(physicalDevice,surface);
        spec.minImageCount = spec.details.capabilities.minImageCount;
        spec.imageFormat = ChooseSurfaceFormat(spec).format;
        spec.imageColorSpace = ChooseSurfaceFormat(spec).colorSpace;
        spec.imageExtent = ChooseSwapExtent(spec,{windowExtent.width,windowExtent.height});
        spec.imageArrayLayers = 1;
        spec.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        spec.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        spec.preTransform = spec.details.capabilities.currentTransform;
        spec.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        spec.presentMode = ChoosePresentMode(spec);
        spec.clipped = VK_TRUE;


        VkSwapchainKHR swapchain{};
        VkSwapchainCreateInfoKHR createInfo{.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
        VkBool32 supported{};
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &supported);
 
        if (!supported)
            LOG_ERROR("Surface is not supported on that device!");

        createInfo.surface = surface;
        createInfo.minImageCount = spec.minImageCount;
        createInfo.imageFormat = spec.imageFormat;
        createInfo.imageColorSpace = spec.imageColorSpace;
        createInfo.imageExtent = spec.imageExtent;
        createInfo.imageArrayLayers = spec.imageArrayLayers;
        createInfo.imageUsage = spec.imageUsage;
        createInfo.imageSharingMode = spec.imageSharingMode;
        createInfo.queueFamilyIndexCount = 1;
        createInfo.pQueueFamilyIndices = &queueFamilyIndex;
        createInfo.preTransform = spec.details.capabilities.currentTransform;
        createInfo.compositeAlpha = spec.compositeAlpha;
        createInfo.presentMode = spec.presentMode;
        createInfo.clipped = spec.clipped;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VK_CHECK(vkCreateSwapchainKHR(device,&createInfo,nullptr,&swapchain));
        LOG_INFO("Swapchain created successfully!");
        return swapchain;
    }

    void SwapchainRecreate(Swapchain& swapchain,VkPhysicalDevice physicalDevice,VkDevice device,ViewportSize size,std::string_view workingDir,std::string_view shaderPath){
        vkDeviceWaitIdle(device);

        SwapchainCleanup(device,swapchain);

        swapchain.swapchain = CreateSwapchain(physicalDevice,
                                              device,
                                              swapchain.SwapchainSpec,
                                              swapchain.Surface,
                                              swapchain.QueueFamilyIndex,
                                              size);
        swapchain.Images = GetSwapchainImages(device,swapchain);
        swapchain.ImageViews = CreateImageViews(device,swapchain);
        swapchain.Renderpass = CreateRenderPass(device,swapchain.SwapchainSpec);
        swapchain.GraphicsPipeline = CreateGraphicsPipeline(device,
                                                            swapchain.SwapchainSpec,
                                                            swapchain.PipelineLayout,
                                                            swapchain.Renderpass,
                                                            Vertex::GetBindingDescription(),
                                                            Vertex::GetAttributeDescriptions(),
                                                            workingDir,
                                                            shaderPath);
        swapchain.Framebuffers = CreateFramebuffers(device,swapchain,size.width,size.height);

    }
    void SwapchainCleanup(VkDevice device,Swapchain& swapchain){
        for (const auto &framebuffer: swapchain.Framebuffers)
            vkDestroyFramebuffer(device,framebuffer,nullptr);
        vkDestroyPipeline(device,swapchain.GraphicsPipeline,nullptr);
        vkDestroyPipelineLayout(device,swapchain.PipelineLayout,nullptr);
        vkDestroyRenderPass(device,swapchain.Renderpass,nullptr);
        for (const auto &view: swapchain.ImageViews)
            vkDestroyImageView(device,view,nullptr);
        vkDestroySwapchainKHR(device,swapchain.swapchain,nullptr);
    }
    VkResult SwapchainAcquireNextImage(Swapchain& swapchain,VkSemaphore semaphore,u32& imageIndex,u32 commandBufferIndex){
        return vkAcquireNextImageKHR(VulkanContext::s_RendererData.device,
                                       swapchain.swapchain,
                                       UINT64_MAX,
                                       semaphore,
                                       VK_NULL_HANDLE,
                                       &imageIndex);

    }

    void BeginRenderPass(std::vector<VkCommandBuffer> commandBuffers, Swapchain &swapchain, uint32_t index) {
        VkRenderPassBeginInfo renderPassInfo{.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        renderPassInfo.renderPass = swapchain.Renderpass;
        renderPassInfo.framebuffer = swapchain.Framebuffers[index];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = {swapchain.FrameSize.width,swapchain.FrameSize.height};

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void EndRenderPass(std::vector<VkCommandBuffer> commandBuffers, uint32_t index) {
        vkCmdEndRenderPass(commandBuffers[index]);
    }

    void BindGraphicsPipeline(std::vector<VkCommandBuffer> commandBuffers,Swapchain& swapchain, uint32_t imageIndex) {
        vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, swapchain.GraphicsPipeline);
    }

    void GraphicsPipelineDraw(std::vector<VkCommandBuffer> commandBuffers, uint32_t imageIndex) {
        vkCmdDraw(commandBuffers[imageIndex],3,1,0,0);
    }

}