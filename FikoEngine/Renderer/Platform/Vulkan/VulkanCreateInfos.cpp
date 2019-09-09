//
// Created by krusto on 1.09.19 г..
//

#include <vector>
#include "VulkanCreateInfos.h"

namespace FikoEngine::VulkanRenderer {

    VulkanCreateInfos::VulkanCreateInfos() {
        setVkApplicationInfo("appName", VK_MAKE_VERSION(1, 0, 0), "FikoEngine", VK_MAKE_VERSION(1, 0, 0),
                             VK_MAKE_VERSION(1, 0, 0));
        setVkInstanceCreateInfo(getApplicationInfo(), mInstanceAttr.Layers.size(), mInstanceAttr.Layers.data(),
                                mInstanceAttr.Extensions.size(), mInstanceAttr.Extensions.data());
        mSwapchainCreateInfo = {};


    }

    void VulkanCreateInfos::setInstanceAttr(std::vector<const char *> *Layers, std::vector<const char *> *Extensions) {
        mInstanceAttr = {*Layers, *Extensions};
        mInstanceCreateInfo.enabledLayerCount = mInstanceAttr.Layers.size();
        mInstanceCreateInfo.ppEnabledLayerNames = mInstanceAttr.Layers.data();
        mInstanceCreateInfo.enabledExtensionCount = mInstanceAttr.Extensions.size();
        mInstanceCreateInfo.ppEnabledExtensionNames = mInstanceAttr.Extensions.data();
    }

    void VulkanCreateInfos::setDeviceAttr(std::vector<const char *> Extensions,
                                          std::vector<VkDeviceQueueCreateInfo> QueueCreateInfo) {
        mDeviceAttr = {Extensions, QueueCreateInfo};
    }

    void VulkanCreateInfos::setQueueFamilyAttr(uint32_t QueueFamilyIndex) {
        mQueueFamilyAttr = {QueueFamilyIndex};
    }

    void VulkanCreateInfos::setAttachmentDescriptionAttr(uint32_t id,VkFormat SurfaceFormat) {
        mAttachmentDescription[id].format = SurfaceFormat;
    }

    VkInstanceCreateInfo *VulkanCreateInfos::getVkInstance() {
        return &mInstanceCreateInfo;
    }

    VkApplicationInfo *VulkanCreateInfos::getApplicationInfo() {
        return &mApplicationInfo;
    }

    VkDeviceCreateInfo *VulkanCreateInfos::getDeviceCreateInfo() {
        return &mDeviceCreateInfo;
    }

    VkDeviceQueueCreateInfo *VulkanCreateInfos::getDeviceQueueCreateInfo(int index) {
        return &mDeviceQueueCreateInfo[index];
    }

    VkDebugReportCallbackCreateInfoEXT *VulkanCreateInfos::getDebugReportCallbackCreateInfo() {
        return &mDebugCallbackCreateInfoEXT;
    }

    VkSwapchainCreateInfoKHR *VulkanCreateInfos::getSwapchainCreateInfo() {
        return &mSwapchainCreateInfo;
    }

#if defined(_LINUX)

    VkXlibSurfaceCreateInfoKHR *VulkanCreateInfos::getXlibSurfaceCreateInfo() {
        return &mXlibSurfaceCreateInfo;
    }

#endif
#if defined(_WIN32)
    VkWin32SurfaceCreateInfoKHR *VulkanCreateInfos::getWin32SurfaceCreateInfo(){
        return &mWin32SurfaceCreateInfoKHR;
    }
#endif

    VkCommandPoolCreateInfo *VulkanCreateInfos::getCommandPoolCreateInfo() {
        return &mCommandPoolCreateInfo;
    }

    VkCommandBufferAllocateInfo *VulkanCreateInfos::getCommandBufferAllocateInfo() {
        return &mCommandBufferAllocateInfo;
    }


    VkAttachmentDescription* VulkanCreateInfos::getAttachmentDescription() {
        return mAttachmentDescription.data();
    }


    VkSubpassDescription *VulkanCreateInfos::getSubpassDescription() {
        return &mSubpassDescription;
    }

    VkSubpassDependency *VulkanCreateInfos::getSubpassDependency() {
        return &mSubpassDependency;
    }

    void VulkanCreateInfos::setVkInstanceCreateInfo(const VkApplicationInfo *pApplicationInfo, uint32_t enabledLayerCount,
                                               const char *const *ppEnabledLayerNames, uint32_t enabledExtensionCount,
                                               const char *const *ppEnabledExtensionNames, VkStructureType sType,
                                               const void *pNext, VkInstanceCreateFlags flags) {
        mInstanceCreateInfo = {sType, pNext, flags, pApplicationInfo, enabledLayerCount, ppEnabledLayerNames,
                               enabledExtensionCount, ppEnabledExtensionNames};
    }

    void VulkanCreateInfos::setVkApplicationInfo(const char *pApplicationName, uint32_t applicationVersion,
                                                 const char *pEngineName, uint32_t engineVersion, uint32_t apiVersion,
                                                 VkStructureType sType, const void *pNext) {
        mApplicationInfo = {sType, pNext, pApplicationName, applicationVersion, pEngineName, engineVersion, apiVersion};
    }

    void VulkanCreateInfos::setVkDeviceCreateInfo(uint32_t queueCreateInfoCount,
                                                  const VkDeviceQueueCreateInfo *pQueueCreateInfos,
                                                  uint32_t enabledExtensionCount,
                                                  const char *const *ppEnabledExtensionNames,
                                                  const VkPhysicalDeviceFeatures *pEnabledFeatures,
                                                  VkStructureType sType, const void *pNext, VkDeviceCreateFlags flags) {

        mDeviceCreateInfo = {sType, pNext, flags, queueCreateInfoCount, pQueueCreateInfos, 0, nullptr,
                             enabledExtensionCount, ppEnabledExtensionNames, pEnabledFeatures};
    }

    void VulkanCreateInfos::setVkQueueCreateInfo(VkDeviceQueueCreateFlags flags, uint32_t queueFamilyIndex,
                                                 uint32_t queueCount, const float *pQueuePriorities,
                                                 VkStructureType sType, const void *pNext) {
        mDeviceQueueCreateInfo.emplace_back(
                (VkDeviceQueueCreateInfo) {sType, pNext, flags, queueFamilyIndex, queueCount, pQueuePriorities});
    }

    void VulkanCreateInfos::setDebugReportCallbackCreateInfo(VkDebugReportFlagsEXT flags,
                                                             PFN_vkDebugReportCallbackEXT pfnCallback, void *pUserData,
                                                             VkStructureType sType, const void *pNext) {
        mDebugCallbackCreateInfoEXT = {sType, pNext, flags, pfnCallback, pUserData};
    }

    void VulkanCreateInfos::setSwapchainCreateInfo(VkSwapchainCreateFlagsKHR flags, VkSurfaceKHR surface,
                                                   uint32_t minImageCount, VkFormat imageFormat,
                                                   VkColorSpaceKHR imageColorSpace, VkExtent2D imageExtent,
                                                   uint32_t imageArrayLayers, VkImageUsageFlags imageUsage,
                                                   VkSharingMode imageSharingMode, uint32_t queueFamilyIndexCount,
                                                   const uint32_t *pQueueFamilyIndices,
                                                   VkSurfaceTransformFlagBitsKHR preTransform,
                                                   VkCompositeAlphaFlagBitsKHR compositeAlpha,
                                                   VkPresentModeKHR presentMode, VkBool32 clipped,
                                                   VkSwapchainKHR oldSwapchain, VkStructureType sType,
                                                   const void *pNext) {
        mSwapchainCreateInfo = {sType, pNext, flags, surface, minImageCount, imageFormat, imageColorSpace, imageExtent,
                                imageArrayLayers, imageUsage, imageSharingMode, queueFamilyIndexCount,
                                pQueueFamilyIndices, preTransform, compositeAlpha, presentMode, clipped, oldSwapchain};
    }

#if defined(_LINUX)
    void VulkanCreateInfos::setXlibSurfaceCreateInfo(Display *dpy,
                                                     Window window,
                                                     VkStructureType sType,
                                                     const void *pNext,
                                                     VkXlibSurfaceCreateFlagsKHR flags) {
        mXlibSurfaceCreateInfo = {sType, pNext, flags, dpy, window};
    }
#endif
#if defined(_WIN32)

#endif
    void VulkanCreateInfos::setCommandPoolCreateInfo(VkCommandPoolCreateFlags flags, uint32_t queueFamilyIndex,
                                                     VkStructureType sType, const void *pNext) {
        mCommandPoolCreateInfo = {sType,pNext,flags,queueFamilyIndex};
    }

    void VulkanCreateInfos::setCommandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level,
                                                         uint32_t commandBufferCount, VkStructureType sType,
                                                         const void *pNext) {
        mCommandBufferAllocateInfo = {sType,pNext,commandPool,level,commandBufferCount};
    }

    void VulkanCreateInfos::setAttachmentDescription(VkAttachmentDescriptionFlags flags, VkSampleCountFlagBits samples,
                                                     VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp,
                                                     VkAttachmentLoadOp stencilLoadOp,
                                                     VkAttachmentStoreOp stencilStoreOp, VkImageLayout initialLayout,
                                                     VkImageLayout finalLayout) {
        mAttachmentDescription.emplace_back((VkAttachmentDescription){flags,VK_FORMAT_UNDEFINED,samples,loadOp,storeOp,stencilLoadOp,stencilStoreOp,initialLayout,finalLayout});
    }

    void
    VulkanCreateInfos::setSubpassDescription(VkSubpassDescriptionFlags flags, VkPipelineBindPoint pipelineBindPoint,
                                             uint32_t inputAttachmentCount,
                                             const VkAttachmentReference *pInputAttachments,
                                             uint32_t colorAttachmentCount,
                                             const VkAttachmentReference *pColorAttachments,
                                             const VkAttachmentReference *pResolveAttachments,
                                             const VkAttachmentReference *pDepthStencilAttachment,
                                             uint32_t preserveAttachmentCount, const uint32_t *pPreserveAttachments) {

        mSubpassDescription = {flags,pipelineBindPoint,inputAttachmentCount,pInputAttachments,colorAttachmentCount,pColorAttachments,pResolveAttachments,pDepthStencilAttachment,preserveAttachmentCount,pPreserveAttachments};
    }

    void
    VulkanCreateInfos::setSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, VkPipelineStageFlags srcStageMask,
                                            VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask,
                                            VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags) {
        mSubpassDependency = {srcSubpass,dstSubpass,srcStageMask,dstStageMask,srcAccessMask,dstAccessMask,dependencyFlags};
    }


}