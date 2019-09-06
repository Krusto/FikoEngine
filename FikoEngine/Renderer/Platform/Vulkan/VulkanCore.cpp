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


VKAPI_ATTR VkBool32 VKAPI_CALL dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
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

namespace FikoEngine::VulkanRenderer{
    void VulkanCore::Init() {
        Log::Init();
        VK_CHECK(mCreateInstance(),"Instance creation Failed ! ");
        VK_CHECK(mSelectPhysicalDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU));
        VK_CHECK(mSelectQueueFamilyIndex());
        VK_CHECK(mCreateDevice());
        VK_CHECK(mCreateDebugCallback());

        VkCommandPoolCreateInfo cmd_pool_info = {};
        cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmd_pool_info.pNext = NULL;
        cmd_pool_info.queueFamilyIndex = mQueueFamilyIndex;
        cmd_pool_info.flags = 0;

        VK_CHECK(vkCreateCommandPool(mDevice, &cmd_pool_info, NULL, &mCommandPool));

        /* Create the command buffer from the command pool */
        VkCommandBufferAllocateInfo cmd;
        cmd.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmd.pNext = nullptr;
        cmd.commandPool = mCommandPool;
        cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmd.commandBufferCount = 1;
        VK_CHECK( vkAllocateCommandBuffers(mDevice, &cmd, &mCommandBuffer));

    }

    VulkanCore::~VulkanCore() {

    }

    VkResult VulkanCore::mCreateInstance() {
        std::vector<const char*> Layers;
        Layers.push_back("VK_LAYER_KHRONOS_validation");

        uint32_t glfwExtensionCount = 0;
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> glfwExtensions (&glfwGetRequiredInstanceExtensions(&glfwExtensionCount)[0],&glfwGetRequiredInstanceExtensions(&glfwExtensionCount)[glfwExtensionCount]);
        glfwExtensions.insert(glfwExtensions.begin(),VK_EXT_DEBUG_REPORT_EXTENSION_NAME);


        createInfo.setInstanceAttr(&Layers,&glfwExtensions);

        return  vkCreateInstance(createInfo.getVkInstance(),nullptr,&mInstance);
    }

    VkResult VulkanCore::mSelectPhysicalDevice(VkPhysicalDeviceType physicalDeviceType) {

        uint32_t deviceCount;

        VK_CHECK(vkEnumeratePhysicalDevices(mInstance,&deviceCount,nullptr),"Can not enumerate physical devices!");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        VK_CHECK(vkEnumeratePhysicalDevices(mInstance,&deviceCount,devices.data()),"Can not enumerate physical devices!");

        for (int i = 0; i < deviceCount; ++i) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(devices[i],&props);
            if(props.deviceType ==  physicalDeviceType){
                mPhysicalDevice = devices[i];
                FIKO_CORE_INFO("Selected Graphical Proccessing Unit with name : " + std::string(props.deviceName)+"\n");
                return VK_SUCCESS;
            }
        }
        if(deviceCount > 0){
            mPhysicalDevice = devices[0];
        }
        FIKO_CORE_INFO("Picked Graphical Proccessing Unit!\n");
        return VK_SUCCESS;
    }

    VkResult VulkanCore::mSelectQueueFamilyIndex() {

        uint32_t size;
        try {
            vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &size, nullptr);
        }catch(std::exception& e){
            VK_CHECK(VkResult::VK_TIMEOUT,"Can not retrieve queue family count");
            return VK_TIMEOUT;
        }
        std::vector<VkQueueFamilyProperties> props(size);
        try {
            vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice,&size,props.data());
        }catch(std::exception& e){
            VK_CHECK(VkResult::VK_TIMEOUT,"Can not retrieve queue family properties");
            return VK_TIMEOUT;
        }

        for (int i = 0; i < size; ++i) {
            if(props[i].queueFlags == VK_QUEUE_COMPUTE_BIT | VK_QUEUE_GRAPHICS_BIT){
                mQueueFamilyIndex = i;
                return VK_SUCCESS;
            }
        }

        return VK_TIMEOUT;
    }

    VkResult VulkanCore::mCreateDevice() {

        createInfo.setQueueFamilyAttr(mQueueFamilyIndex);
        const float priorities = {0.00};

        createInfo.setVkQueueCreateInfo(0,mQueueFamilyIndex,1,&priorities);

        createInfo.setVkDeviceCreateInfo(1,createInfo.getDeviceQueueCreateInfo(0),0,nullptr,nullptr);

        return vkCreateDevice(mPhysicalDevice,createInfo.getDeviceCreateInfo(),nullptr,&mDevice);
    }
    VkResult VulkanCore::mCreateDebugCallback(){

        PFN_vkCreateDebugReportCallbackEXT dbgCreateDebugReportCallback =
                (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(mInstance, "vkCreateDebugReportCallbackEXT");
        if (!dbgCreateDebugReportCallback) {
            std::cout << "GetInstanceProcAddr: Unable to find "
                         "vkCreateDebugReportCallbackEXT function."
                      << std::endl;
            exit(1);
        }
        createInfo.setDebugReportCallbackCreateInfo(VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT,dbgFunc);
        return dbgCreateDebugReportCallback(mInstance, createInfo.getDebugReportCallbackCreateInfo(), NULL, &mDebugReportCallback);
    }
}