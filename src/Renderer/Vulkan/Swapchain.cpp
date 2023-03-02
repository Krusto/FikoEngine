#include "Swapchain.h"
#include "VulkanRenderer.h"

#include "Queue.h"
#include "Memory.h"
#include "Image.h"
#include "ImageView.h"
#include "Renderpass.h"
#include "GraphicsPipeline.h"
#include "Framebuffer.h"
#include "../Vertex.h"

namespace FikoEngine {
    void Swapchain::Create() {
        m_SwapchainSpec.details = GetSwapchainSupportDetails(VulkanRenderer::s_RendererData.physicalDevice,
                                                             VulkanRenderer::s_RendererData.surface);
        m_SwapchainSpec.minImageCount = m_SwapchainSpec.details.capabilities.minImageCount;
        m_SwapchainSpec.imageFormat = ChooseSurfaceFormat(m_SwapchainSpec).format;
        m_SwapchainSpec.imageColorSpace = ChooseSurfaceFormat(m_SwapchainSpec).colorSpace;
        m_SwapchainSpec.imageExtent = ChooseSwapExtent(m_SwapchainSpec,
                                                       {VulkanRenderer::s_RendererData.rendererSpec.SurfaceSize.width,
                                                        VulkanRenderer::s_RendererData.rendererSpec.SurfaceSize.height});
        m_SwapchainSpec.imageArrayLayers = 1;
        m_SwapchainSpec.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        m_SwapchainSpec.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        m_SwapchainSpec.preTransform = m_SwapchainSpec.details.capabilities.currentTransform;
        m_SwapchainSpec.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        m_SwapchainSpec.presentMode = ChoosePresentMode(m_SwapchainSpec);
        m_SwapchainSpec.clipped = VK_TRUE;

        m_Swapchain = CreateSwapchain(VulkanRenderer::s_RendererData.physicalDevice,
                                      VulkanRenderer::s_RendererData.device,
                                      m_SwapchainSpec,
                                      VulkanRenderer::s_RendererData.surface,
                                      VulkanRenderer::s_RendererData.queueFamilyIndex,
                                      m_SwapchainSpec .frameSize);

        m_Images = GetSwapchainImages(VulkanRenderer::s_RendererData.device,m_Swapchain);
        m_ImageViews = CreateImageViews(VulkanRenderer::s_RendererData.device,this);
    }

    void Swapchain::Recreate(){
        vkDeviceWaitIdle(VulkanRenderer::s_RendererData.device);

        Cleanup();

        Create();
    }
    void Swapchain::Cleanup(){
        for (const auto &view: m_ImageViews)
            vkDestroyImageView(VulkanRenderer::s_RendererData.device,view,nullptr);
        vkDestroySwapchainKHR(VulkanRenderer::s_RendererData.device,m_Swapchain,nullptr);

    }

    VkSwapchainKHR& Swapchain::GetSwapchain() {
        return m_Swapchain;
    }

    const std::vector<VkImage> &Swapchain::GetImages() const {
        return m_Images;
    }

    const std::vector<VkImageView> &Swapchain::GetImageViews() const {
        return m_ImageViews;
    }

    const SwapChainSpec &Swapchain::GetSwapchainSpec() const {
        return m_SwapchainSpec;
    }

    SwapChainSpec &Swapchain::GetSwapchainSpec(){
        return m_SwapchainSpec;
    }

    const VkSurfaceKHR *Swapchain::GetSurface() const {
        return &m_Surface;
    }

    void Swapchain::SetSurface(VkSurfaceKHR surface) {
        m_Surface = surface;
    }

    bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::string_view extension) {
        u32 extensionCount{};
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
        return swapchain;
    }

    VkResult SwapchainAcquireNextImage(Ref<Swapchain> swapchain,VkSemaphore semaphore,u32& imageIndex){
        return vkAcquireNextImageKHR(VulkanRenderer::s_RendererData.device,
                                       swapchain->GetSwapchain(),
                                       UINT64_MAX,
                                       semaphore,
                                       VK_NULL_HANDLE,
                                       &imageIndex);

    }

    void BeginRenderPass(std::vector<VkCommandBuffer> commandBuffers, Ref<Swapchain> swapchain, u32 index) {
        VkRenderPassBeginInfo renderPassInfo{.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        renderPassInfo.renderPass = VulkanRenderer::s_RendererData.renderPass;
        renderPassInfo.framebuffer = VulkanRenderer::s_RendererData.framebuffer->VulkanData()[index];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = {swapchain->GetSwapchainSpec().frameSize.width,swapchain->GetSwapchainSpec().frameSize.height};

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void EndRenderPass(std::vector<VkCommandBuffer> commandBuffers, u32 index) {
        vkCmdEndRenderPass(commandBuffers[index]);
    }

    void BindGraphicsPipeline(std::vector<VkCommandBuffer> commandBuffers,Ref<VulkanShader> shader, u32 imageIndex) {
        vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, shader->getPipeline());
    }

    void GraphicsPipelineDraw(std::vector<VkCommandBuffer> commandBuffers, u32 imageIndex) {
        vkCmdDraw(commandBuffers[imageIndex],3,1,0,0);
    }
    void GraphicsPipelineDrawIndexed(std::vector<VkCommandBuffer> commandBuffers, u32 imageIndex,u32 indexCount) {
        vkCmdDrawIndexed(commandBuffers[imageIndex],indexCount,0,0,0,0);
    }

}