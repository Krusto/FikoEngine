//
// Created by krusto on 31.08.19 г..
//
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "VulkanCore.h"
#include "VulkanUtilities.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3native.h>


namespace FikoEngine::VulkanRenderer {

#if defined(_DEBUG)
    VKAPI_ATTR VkBool32 VKAPI_CALL
    dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
            size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
            void *pUserData) {
        std::ostringstream message;

        if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
            message << "ERROR: ";
        } else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
            message << "WARNING: ";
        } else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
            message << "PERFORMANCE WARNING: ";
        } else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
            message << "INFO: ";
        } else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
            message << "DEBUG: ";
        }
        message << "[" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg;

#ifdef _WIN32
        MessageBox(NULL, message.str().c_str(), "Alert", MB_OK);
#else
        std::cout << message.str() << std::endl;
#endif

        /*
         * false indicates that layer should not bail-out of an
         * API call that had validation failures. This may mean that the
         * app dies inside the driver due to invalid parameter(s).
         * That's what would happen without validation layers, so we'll
         * keep that behavior here.
         */
        return false;
    }

#endif

    void VulkanCore::Init(FikoEngine::Window window) {
        mWindow = &window;
        Log::Init();
        VK_CHECK(mCreateInstance(), "Instance creation Failed!");
#if defined(_DEBUG)
        VK_CHECK(mCreateDebugCallback(), "Can not create Debug Callback!");
#endif
        VK_CHECK(mSelectPhysicalDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU), "Can not select graphical adapter!");
        VK_CHECK(mSelectQueueFamilyIndex(), "Can not find queue!");
        VK_CHECK(mCreateDevice(), "Can not create VkDevice!");
        VK_CHECK(mGetSurface(), "Can not get surface!");
        VK_CHECK(mCreateSwapchainKHR(), "Can not create VkSwapchainKHR!");
        VK_CHECK(mCreateCommandPool(),"Can not create VkCommandPool!");
        VK_CHECK(mAllocateCommandBuffers(),"Can not allocate command buffers!");
        VK_CHECK(mGetSwapchainImages(),"Can not get swapchain images!");
        VK_CHECK(mGetSwapchainImagesView(),"Can not get swapchain images view!");
        VK_CHECK(mCreateSemaphores(),"Can not create semaphores!");
        VK_CHECK(mCreateRenderpass(),"Can not create renderpass!");
    }

    VulkanCore::~VulkanCore() {
        vkDestroySwapchainKHR(mDevice,mSwapchain,nullptr);
        vkDestroySurfaceKHR(mInstance,mSurface,nullptr);
        vkDestroyDevice(mDevice,nullptr);
        vkDestroyInstance(mInstance,nullptr);
    }

    VkResult VulkanCore::mCreateInstance() {
        std::vector<const char *> Layers;
#if defined(_DEBUG)
        Layers.push_back("VK_LAYER_KHRONOS_validation");
#endif
        uint32_t glfwExtensionCount = 0;
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> glfwExtensions(&glfwGetRequiredInstanceExtensions(&glfwExtensionCount)[0],
                                                 &glfwGetRequiredInstanceExtensions(
                                                         &glfwExtensionCount)[glfwExtensionCount]);

#if defined(_DEBUG)
        glfwExtensions.insert(glfwExtensions.begin(), VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif
#if defined(_LINUX)
        glfwExtensions.emplace_back("VK_KHR_xlib_surface");
#endif
#if defined(_WIN32)
        glfwExtensions.emplace_back("VK_KHR_win32_surface");
#endif

        createInfo.setInstanceAttr(&Layers, &glfwExtensions);

        return vkCreateInstance(createInfo.getVkInstance(), nullptr, &mInstance);
    }

    VkResult VulkanCore::mSelectPhysicalDevice(VkPhysicalDeviceType physicalDeviceType) {

        uint32_t deviceCount;

        VK_CHECK(vkEnumeratePhysicalDevices(mInstance, &deviceCount, nullptr), "Can not enumerate physical devices!");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        VK_CHECK(vkEnumeratePhysicalDevices(mInstance, &deviceCount, devices.data()),
                 "Can not enumerate physical devices!");

        for (int i = 0; i < deviceCount; ++i) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(devices[i], &props);
            if (props.deviceType == physicalDeviceType) {
                mPhysicalDevice = devices[i];
                FIKO_CORE_INFO(
                        "Selected Graphical Proccessing Unit with name : " + std::string(props.deviceName) + "\n");
                return VK_SUCCESS;
            }
        }
        if (deviceCount > 0) {
            mPhysicalDevice = devices[0];
        }
        FIKO_CORE_INFO("Picked Graphical Proccessing Unit!\n");
        return VK_SUCCESS;
    }

    VkResult VulkanCore::mSelectQueueFamilyIndex() {

        uint32_t size;
        try {
            vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &size, nullptr);
        } catch (std::exception &e) {
            VK_CHECK(VkResult::VK_TIMEOUT, "Can not retrieve queue family count");
            return VK_TIMEOUT;
        }
        std::vector<VkQueueFamilyProperties> props(size);
        try {
            vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &size, props.data());
        } catch (std::exception &e) {
            VK_CHECK(VkResult::VK_TIMEOUT, "Can not retrieve queue family properties");
            return VK_TIMEOUT;
        }

        for (int i = 0; i < size; ++i) {
            if (props[i].queueFlags == VK_QUEUE_COMPUTE_BIT | VK_QUEUE_GRAPHICS_BIT) {
                mQueueFamilyIndex = i;
                return VK_SUCCESS;
            }
        }

        return VK_TIMEOUT;
    }

    VkResult VulkanCore::mCreateDevice() {

//TODO
        createInfo.setQueueFamilyAttr(mQueueFamilyIndex);
        const float priorities = {0.00};
        createInfo.setVkQueueCreateInfo(0, mQueueFamilyIndex, 1, &priorities);

        std::vector<const char*> deviceExtensions;
        deviceExtensions.emplace_back("VK_KHR_swapchain");
        deviceExtensions.emplace_back("VK_KHR_maintenance2");
        deviceExtensions.emplace_back("VK_KHR_image_format_list");
        deviceExtensions.emplace_back("VK_KHR_swapchain_mutable_format");

        createInfo.setVkDeviceCreateInfo(1, createInfo.getDeviceQueueCreateInfo(0),deviceExtensions.size(), deviceExtensions.data(), nullptr);

        return vkCreateDevice(mPhysicalDevice, createInfo.getDeviceCreateInfo(), nullptr, &mDevice);
    }

#if defined(_DEBUG)
    VkResult VulkanCore::mCreateDebugCallback() {

        auto dbgCreateDebugReportCallback =
                (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(mInstance, "vkCreateDebugReportCallbackEXT");
        if (!dbgCreateDebugReportCallback) {
            FIKO_CORE_ERROR( "GetInstanceProcAddr: Unable to find "
                         "vkCreateDebugReportCallbackEXT function.");
        }


        createInfo.setDebugReportCallbackCreateInfo(VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT,
                                                    dbgFunc);

        return dbgCreateDebugReportCallback(mInstance, createInfo.getDebugReportCallbackCreateInfo(), NULL,
                                            &mDebugReportCallback);
    }
#endif

    VkResult VulkanCore::mGetSurface() {
#if defined(_LINUX)
        createInfo.setXlibSurfaceCreateInfo(glfwGetX11Display(), glfwGetX11Window(mWindow->GetInstance()));
        return vkCreateXlibSurfaceKHR(mInstance, createInfo.getXlibSurfaceCreateInfo(), nullptr, &mSurface);
#endif
#if defined(_WIN32)
        return VK_TIMEOUT;
#endif
    }

    VkResult VulkanCore::mCreateSwapchainKHR() {

        //TODO This needs to be cleaned

        std::vector<VkSurfaceFormatKHR>formatsKHR;
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &formatCount, nullptr);
        formatsKHR.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &formatCount, formatsKHR.data());
        mSurfaceFormat = formatsKHR[0];

        VkSurfaceCapabilitiesKHR capabilitiesKHR;
        VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice,mSurface, &capabilitiesKHR));

        VkBool32 supported;
        vkGetPhysicalDeviceSurfaceSupportKHR(mPhysicalDevice,mQueueFamilyIndex,mSurface,&supported);



        createInfo.setSwapchainCreateInfo(  VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
                                            mSurface,
                                            capabilitiesKHR.minImageCount,
                                            mSurfaceFormat.format,
                                            mSurfaceFormat.colorSpace,
                                            capabilitiesKHR.currentExtent,
                                           1,
                                           VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                           VK_SHARING_MODE_EXCLUSIVE,
                                           1,
                                            &mQueueFamilyIndex,
                                           capabilitiesKHR.currentTransform,
                                           VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                                           VK_PRESENT_MODE_FIFO_KHR,
                                            VK_TRUE,
                                            VK_NULL_HANDLE
                                            );

       return vkCreateSwapchainKHR(mDevice,createInfo.getSwapchainCreateInfo(),nullptr,&mSwapchain);
    }

    VkResult VulkanCore::mCreateCommandPool() {
        createInfo.setCommandPoolCreateInfo(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,mQueueFamilyIndex);
        return vkCreateCommandPool(mDevice,createInfo.getCommandPoolCreateInfo(),nullptr,&mCommandPool);
    }

    VkResult VulkanCore::mAllocateCommandBuffers() {

        mCommandBuffers.resize(1);
        createInfo.setCommandBufferAllocateInfo(mCommandPool,VK_COMMAND_BUFFER_LEVEL_PRIMARY,mCommandBuffers.size());

        return vkAllocateCommandBuffers(mDevice,createInfo.getCommandBufferAllocateInfo(),mCommandBuffers.data());
    }

    VkResult VulkanCore::mGetSwapchainImages() {
        uint32_t count;

        VK_CHECK(vkGetSwapchainImagesKHR(mDevice, mSwapchain, &count, nullptr),"Can not get swapchain image count!");

        VK_CHECK((count >=2 )? VK_SUCCESS : VK_TIMEOUT,"Swap chain image count is not correct!");

        mSwapchainImages = std::vector<VkImage>(count);
        VK_CHECK(vkGetSwapchainImagesKHR(mDevice, mSwapchain, &count, mSwapchainImages.data()),"Can not get swapchain images!");

        return VK_SUCCESS;
    }

    VkResult VulkanCore::mGetSwapchainImagesView() {
        mSwapchainImagesView.resize(mSwapchainImages.size());
        for (uint32_t i = 0; i < mSwapchainImages.size(); i++)
        {
            VkImageViewCreateInfo imageViewCreateInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
            imageViewCreateInfo.image = mSwapchainImages[i];
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.format = mSurfaceFormat.format;
            imageViewCreateInfo.components = {VK_COMPONENT_SWIZZLE_R,VK_COMPONENT_SWIZZLE_G,VK_COMPONENT_SWIZZLE_B,VK_COMPONENT_SWIZZLE_A};
            imageViewCreateInfo.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT,0,1,0,1};

            VK_CHECK(vkCreateImageView(mDevice, &imageViewCreateInfo, nullptr, &mSwapchainImagesView[i]),"Can not create image view with id:" + std::to_string(i)+" !");
        }
        return VK_SUCCESS;
    }

    VkResult VulkanCore::mCreateSemaphores() {

        VkSemaphoreCreateInfo semaphoreCreateInfo= {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        VK_CHECK(vkCreateSemaphore(mDevice,&semaphoreCreateInfo,nullptr,&mWaitSemaphore),"Can not create wait semaphore!");
        VK_CHECK(vkCreateSemaphore(mDevice,&semaphoreCreateInfo,nullptr,&mSignalSemaphore),"Can not create signal semaphore!");
        return VK_SUCCESS;
    }

    VkResult VulkanCore::mCreateRenderpass() {
        createInfo.setAttachmentDescription(0,VK_SAMPLE_COUNT_1_BIT,VK_ATTACHMENT_LOAD_OP_CLEAR,VK_ATTACHMENT_STORE_OP_STORE,VK_ATTACHMENT_LOAD_OP_DONT_CARE,VK_ATTACHMENT_STORE_OP_DONT_CARE,VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        createInfo.setAttachmentDescriptionAttr(0,mSurfaceFormat.format);

        VkAttachmentReference colorAttachments = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

        createInfo.setSubpassDescription(0,
                              VK_PIPELINE_BIND_POINT_GRAPHICS,
                              0,
                              nullptr,
                              1,
                              &colorAttachments,
                              nullptr,
                              nullptr,
                              0,
                              nullptr);

        createInfo.setSubpassDependency(VK_SUBPASS_EXTERNAL,0,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,0,VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,0);

        VkRenderPassCreateInfo passCreateInfo ={VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
        passCreateInfo.attachmentCount = 1;
        passCreateInfo.pAttachments = &createInfo.getAttachmentDescription()[0];
        passCreateInfo.subpassCount = 1;
        passCreateInfo.pSubpasses = createInfo.getSubpassDescription();
        passCreateInfo.dependencyCount = 1;
        passCreateInfo.pDependencies = createInfo.getSubpassDependency();

        return vkCreateRenderPass(mDevice,&passCreateInfo,nullptr,&mRenderPass);
    }

}