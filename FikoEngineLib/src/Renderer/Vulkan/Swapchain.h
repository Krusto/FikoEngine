//
// Created by Stoyanov, Krusto (K.S.) on 6/10/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include "Core/Ref.h"
#include "SwapchainSpec.h"
#include "Renderer/Viewport.h"
#include "VulkanShader.h"

namespace FikoEngine {

    class Swapchain : public RefCounted{
    public:
        Swapchain(){ Create(); };
        Swapchain& operator=(Swapchain&) = default;

    public:
        void Recreate();
        void Cleanup();

    public:
        uint32_t FramesCount;
        uint32_t QueueFamilyIndex;

    private:
        VkSwapchainKHR m_Swapchain;

        std::vector<VkImage> m_Images;
        std::vector<VkImageView> m_ImageViews;
        SwapChainSpec m_SwapchainSpec;
        VkSurfaceKHR m_Surface;

    public:
        VkSwapchainKHR& GetSwapchain();

        const std::vector<VkImage> &GetImages() const;

        const std::vector<VkImageView> &GetImageViews() const;

        const SwapChainSpec &GetSwapchainSpec() const;
        SwapChainSpec &GetSwapchainSpec();

        const VkSurfaceKHR *GetSurface() const;

        void SetSurface(VkSurfaceKHR surface);

    public:
        operator VkSwapchainKHR(){
            return m_Swapchain;
        }
        operator VkSwapchainKHR&(){
            return m_Swapchain;
        }

    private:
        void Create();
    };

    bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::string_view extension);

    bool CheckSwapChainSupport(VkPhysicalDevice physicalDevice);

    SwapChainSupportDetails GetSwapchainSupportDetails(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface);

    VkSurfaceFormatKHR ChooseSurfaceFormat(SwapChainSpec& spec);

    VkPresentModeKHR ChoosePresentMode(SwapChainSpec& spec);

    VkExtent2D ChooseSwapExtent(SwapChainSpec& spec,VkExtent2D windowExtent);

    VkSwapchainKHR CreateSwapchain(VkPhysicalDevice physicalDevice,VkDevice device,SwapChainSpec& spec,VkSurfaceKHR surface,uint32_t queueFamilyIndex,ViewportSize windowExtent);

    VkResult SwapchainAcquireNextImage(Ref<Swapchain> swapchain,VkSemaphore semaphore,uint32_t& imageIndex);

    void BeginRenderPass(std::vector<VkCommandBuffer> commandBuffers,Ref<Swapchain> swapchain, uint32_t index);
    void EndRenderPass(std::vector<VkCommandBuffer> commandBuffers,uint32_t index);

    void BindGraphicsPipeline(std::vector<VkCommandBuffer> commandBuffers,Ref<VulkanShader> shader,uint32_t imageIndex);
    void GraphicsPipelineDraw(std::vector<VkCommandBuffer> commandBuffers,uint32_t imageIndex);
    void GraphicsPipelineDrawIndexed(std::vector<VkCommandBuffer> commandBuffers,uint32_t imageIndex,uint32_t indexCount);
}