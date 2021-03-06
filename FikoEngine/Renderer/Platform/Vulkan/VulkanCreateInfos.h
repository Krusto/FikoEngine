//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_VULKANCREATEINFOS_H
#define FIKOENGINE_VULKANCREATEINFOS_H

#include <vulkan/vulkan.h>
#include <vector>

namespace FikoEngine::VulkanRenderer {
    class VulkanCreateInfos {
    public:
        VulkanCreateInfos();

        void setInstanceAttr(std::vector<const char *> *Layers, std::vector<const char *> *Extensions);

        void setDeviceAttr(std::vector<const char *> Extensions, std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos);

        void setQueueFamilyAttr(uint32_t QueueFamilyIndex);

        void setAttachmentDescriptionAttr(uint32_t id,VkFormat SurfaceFormat);

        VkInstanceCreateInfo *getVkInstance();

        VkApplicationInfo *getApplicationInfo();

        VkDeviceCreateInfo *getDeviceCreateInfo();

        VkDeviceQueueCreateInfo *getDeviceQueueCreateInfo(int index);

        VkDebugReportCallbackCreateInfoEXT *getDebugReportCallbackCreateInfo();

        VkSwapchainCreateInfoKHR *getSwapchainCreateInfo();

#if defined(_LINUX)
        VkXlibSurfaceCreateInfoKHR *getXlibSurfaceCreateInfo();
#endif
#if defined(_WIN32)
        VkWin32SurfaceCreateInfoKHR* getWin32SurfaceCreateInfo();
#endif

        VkCommandPoolCreateInfo *getCommandPoolCreateInfo();


        VkCommandBufferAllocateInfo *getCommandBufferAllocateInfo();

        VkAttachmentDescription* getAttachmentDescription();

        VkSubpassDescription *getSubpassDescription();

        VkSubpassDependency *getSubpassDependency();

        void setVkInstanceCreateInfo(const VkApplicationInfo *pApplicationInfo,
                                     uint32_t enabledLayerCount,
                                     const char *const *ppEnabledLayerNames,
                                     uint32_t enabledExtensionCount,
                                     const char *const *ppEnabledExtensionNames,
                                     VkStructureType sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                     const void *pNext = nullptr,
                                     VkInstanceCreateFlags flags = 0);

        void setVkApplicationInfo(const char *pApplicationName,
                                  uint32_t applicationVersion,
                                  const char *pEngineName,
                                  uint32_t engineVersion,
                                  uint32_t apiVersion,
                                  VkStructureType sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                  const void *pNext = nullptr);

        void setVkQueueCreateInfo(VkDeviceQueueCreateFlags flags,
                                  uint32_t queueFamilyIndex,
                                  uint32_t queueCount,
                                  const float *pQueuePriorities,
                                  VkStructureType sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                  const void *pNext = nullptr);

        void setVkDeviceCreateInfo(uint32_t queueCreateInfoCount,
                                   const VkDeviceQueueCreateInfo *pQueueCreateInfos,
                                   uint32_t enabledExtensionCount,
                                   const char *const *ppEnabledExtensionNames,
                                   const VkPhysicalDeviceFeatures *pEnabledFeatures,
                                   VkStructureType sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                                   const void *pNext = nullptr,
                                   VkDeviceCreateFlags flags = 0);

        void setDebugReportCallbackCreateInfo(VkDebugReportFlagsEXT flags,
                                              PFN_vkDebugReportCallbackEXT pfnCallback,
                                              void *pUserData = nullptr,
                                              VkStructureType sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
                                              const void *pNext = nullptr);

#if defined(_LINUX)
        void setXlibSurfaceCreateInfo(Display *dpy,
                                      Window window,
                                      VkStructureType sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
                                      const void *pNext = nullptr,
                                      VkXlibSurfaceCreateFlagsKHR flags = 0);
#endif
#if defined(_WIN32)
#endif

        void setSwapchainCreateInfo(VkSwapchainCreateFlagsKHR flags,
                                    VkSurfaceKHR surface,
                                    uint32_t minImageCount,
                                    VkFormat imageFormat,
                                    VkColorSpaceKHR imageColorSpace,
                                    VkExtent2D imageExtent,
                                    uint32_t imageArrayLayers,
                                    VkImageUsageFlags imageUsage,
                                    VkSharingMode imageSharingMode,
                                    uint32_t queueFamilyIndexCount,
                                    const uint32_t *pQueueFamilyIndices,
                                    VkSurfaceTransformFlagBitsKHR preTransform,
                                    VkCompositeAlphaFlagBitsKHR compositeAlpha,
                                    VkPresentModeKHR presentMode,
                                    VkBool32 clipped,
                                    VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE,
                                    VkStructureType sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                                    const void *pNext = nullptr
        );

        void setCommandPoolCreateInfo(  VkCommandPoolCreateFlags    flags,
                                        uint32_t                    queueFamilyIndex,
                                        VkStructureType             sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                                        const void*                 pNext = nullptr);

        void setCommandBufferAllocateInfo(  VkCommandPool           commandPool,
                                            VkCommandBufferLevel    level,
                                            uint32_t                commandBufferCount,
                                            VkStructureType         sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                                            const void*             pNext = nullptr);

        void setAttachmentDescription(  VkAttachmentDescriptionFlags    flags,
                                        VkSampleCountFlagBits           samples,
                                        VkAttachmentLoadOp              loadOp,
                                        VkAttachmentStoreOp             storeOp,
                                        VkAttachmentLoadOp              stencilLoadOp,
                                        VkAttachmentStoreOp             stencilStoreOp,
                                        VkImageLayout                   initialLayout,
                                        VkImageLayout                   finalLayout);

        void setSubpassDescription( VkSubpassDescriptionFlags       flags,
                                    VkPipelineBindPoint             pipelineBindPoint,
                                    uint32_t                        inputAttachmentCount,
                                    const VkAttachmentReference*    pInputAttachments,
                                    uint32_t                        colorAttachmentCount,
                                    const VkAttachmentReference*    pColorAttachments,
                                    const VkAttachmentReference*    pResolveAttachments,
                                    const VkAttachmentReference*    pDepthStencilAttachment,
                                    uint32_t                        preserveAttachmentCount,
                                    const uint32_t*                 pPreserveAttachments);

        void setSubpassDependency(  uint32_t                srcSubpass,
                                    uint32_t                dstSubpass,
                                    VkPipelineStageFlags    srcStageMask,
                                    VkPipelineStageFlags    dstStageMask,
                                    VkAccessFlags           srcAccessMask,
                                    VkAccessFlags           dstAccessMask,
                                    VkDependencyFlags       dependencyFlags);


    private:
        VkInstanceCreateInfo mInstanceCreateInfo;
        VkApplicationInfo mApplicationInfo;
        VkDeviceCreateInfo mDeviceCreateInfo;
        VkDebugReportCallbackCreateInfoEXT mDebugCallbackCreateInfoEXT;

        std::vector<VkDeviceQueueCreateInfo> mDeviceQueueCreateInfo;

#if defined(_LINUX)
        VkXlibSurfaceCreateInfoKHR mXlibSurfaceCreateInfo;
#endif
#if defined(_WIN32)
        VkWin32SurfaceCreateInfoKHR mWin32SurfaceCreateInfo;
#endif
        VkSwapchainCreateInfoKHR mSwapchainCreateInfo;

        VkCommandPoolCreateInfo mCommandPoolCreateInfo;

        VkCommandBufferAllocateInfo mCommandBufferAllocateInfo;

        std::vector<VkAttachmentDescription> mAttachmentDescription;

        VkSubpassDescription mSubpassDescription;

        VkSubpassDependency mSubpassDependency;

        VkPipelineShaderStageCreateInfo mPipelineShaderStage;

    private:
        struct mInstanceAttr {
            std::vector<const char *> Layers;
            std::vector<const char *> Extensions;
        } mInstanceAttr;
        struct mDeviceAttr {
            std::vector<const char *> Extensions;
            std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
        } mDeviceAttr;
        struct mQueueFamilyAttr {
            uint32_t queueFamilyIndex;
        } mQueueFamilyAttr;
    };
}

#endif //FIKOENGINE_VULKANCREATEINFOS_H
