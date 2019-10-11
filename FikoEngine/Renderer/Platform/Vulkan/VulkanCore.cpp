//
// Created by krusto on 31.08.19 г..
//
#include <iostream>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include "VulkanCore.h"
#include "VulkanUtilities.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3native.h>
#include "Core/Instance.h"
#include "Core/Debug.h"
#include "Core/Device.h"
#include "Core/Queue.h"
#include "Core/Surface.h"
#include "Core/Swapchain.h"
#include "AllocationManger.h"
#include "Core/Renderpass.h"
#include "Core/GraphicsPipeline.h"

namespace FikoEngine::VulkanRenderer {
    std::vector<VkCommandBuffer> CommandBuffer::commandBuffers;
    void VulkanCore::Init(FikoEngine::Window window) {
        mWindow = &window;
        Log::Init();

        createInfo = VulkanCreateInfos();

        mInstance = Instance::Init(true);

#if defined(_DEBUG)
        VK_CHECK(Debug::enableDebug(mInstance,&mDebugReportCallback), "Can not create Debug Callback!");
#endif

        mPhysicalDevices = PhysicalDevice::Enumerate(mInstance);
        mPhysicalDevice = PhysicalDevice::Select(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,mPhysicalDevices);
        mQueueFamilyIndex = QueueFamilyIndex::Select(mPhysicalDevice, VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
        mDevice = LogicalDevice::Create(mQueueFamilyIndex,mPhysicalDevice);
        mSurface = Surface::getSurface(mInstance,mWindow->GetInstance());

        std::pair<VkSwapchainKHR ,VkSurfaceFormatKHR> temp = Swapchain::createSwapchain(mPhysicalDevice,mDevice,mSurface,mQueueFamilyIndex);
        mSurfaceFormat = temp.second;
        mSwapchain = temp.first;

        mCommandPool = CommandPool::createCommandPool(mDevice,mQueueFamilyIndex);
        CommandBuffer::allocateCommandBuffer(mDevice,mCommandPool,2);

        mSwapchainImages = Swapchain::getSwapchainImages(mDevice,mSwapchain);
        mSwapchainImagesView = Swapchain::getSwapchainImagesView(mDevice,mSwapchainImages,mSurfaceFormat);

        VK_CHECK(mCreateSemaphores(),"Can not create semaphores!");

        mRenderPass = RenderPass::CreateRenderpass(mDevice,mSurfaceFormat);

//        mGraphicsPipeline = GraphicsPipeline::Create(mDevice,"./vert.sh","./frag.sh",mWindow);
    }


    void VulkanCore::Begin() {
        VkQueue mQueue;

        vkGetDeviceQueue(mDevice,mQueueFamilyIndex,0,&mQueue);

        mAcquireNextImage();

        CommandPool::Reset(mDevice,mCommandPool);
        CommandBuffer::Begin(0);

        VkClearColorValue color = { 1,0,1,1 };
        VkClearValue clearColor = { color };

/*        mCmdDraw();
        vkCmdDraw(mCommandBuffers[mSwapchainImageIndex], 3, 1, 0, 0);

        mBeginRenderPass(&clearColor, m_Window);
        mEndRenderPass();

        CommandBuffer::End(mSwapchainImageIndex);

        mSubmitToQueue(mSwapchainImageIndex, mQueue);
        mQueuePresentKHR(mQueue);*/
    }

    void VulkanCore::End() {

    }

    VulkanCore::~VulkanCore() {
    }


    VkResult VulkanCore::mCreateSemaphores() {

        VkSemaphoreCreateInfo semaphoreCreateInfo= {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        VK_CHECK(vkCreateSemaphore(mDevice,&semaphoreCreateInfo,nullptr,&mWaitSemaphore),"Can not create wait semaphore!");
        VK_CHECK(vkCreateSemaphore(mDevice,&semaphoreCreateInfo,nullptr,&mSignalSemaphore),"Can not create signal semaphore!");
        return VK_SUCCESS;
    }

    void VulkanCore::mAcquireNextImage() {
        VK_CHECK(vkAcquireNextImageKHR(mDevice, mSwapchain, (std::numeric_limits<unsigned long long>::max)(), mSignalSemaphore, VK_NULL_HANDLE, &mSwapchainImageIndex));
    }


}