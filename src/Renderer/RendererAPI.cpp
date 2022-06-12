//
// Created by KSTOYAN2 on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include <lwlog.h>
#include "RendererAPI.h"
#include "Window.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"
#include "Vulkan/Device.h"
#include "Vulkan/Swapchain.h"
#include "Vulkan/ImageView.h"
#include "Vulkan/Image.h"
#include "Vulkan/RendererData.h"
#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/Renderpass.h"
#include "Memory.h"

namespace FikoEngine {
    static QueueFamilyIndices s_RendererQueueFamilyIndices;

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererData.workingDir = applicationSpec.WorkingDirectory;
        s_RendererData.instance =  CreateInstance(applicationSpec);
        s_RendererData.physicalDevice = SelectPhysicalDevice(s_RendererData);

        rendererSpec.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        s_RendererData.device = CreateDevice(s_RendererData,rendererSpec.extensions);
        s_RendererData.surface = applicationSpec.window->CreateSurface(s_RendererData.instance);
        s_RendererData.swapchain = CreateSwapchain(s_RendererData,{rendererSpec.SurfaceWidth,rendererSpec.SurfaceHeight});
        s_RendererData.swapchainImages = GetSwapchainImages(s_RendererData);
        s_RendererData.imageViews = CreateImageViews(s_RendererData);
        s_RendererData.renderPass = CreateRenderPass(s_RendererData);
        s_RendererData.graphicsPipeline = CreateGraphicsPipeline(s_RendererData,"assets/basic");

        LOG("Renderer initialized!");

        vkDestroyPipeline(s_RendererData.device,s_RendererData.graphicsPipeline,CreatePAllocator("Graphics pipeline"));
        vkDestroyPipelineLayout(s_RendererData.device,s_RendererData.pipelineLayout,CreatePAllocator("Pipeline layout"));
        vkDestroyRenderPass(s_RendererData.device,s_RendererData.renderPass,CreatePAllocator("Pipeline layout"));
        for (const auto &view: s_RendererData.imageViews)
            vkDestroyImageView(s_RendererData.device,view,CreatePAllocator("Image View"));
        vkDestroySwapchainKHR(s_RendererData.device,s_RendererData.swapchain,CreatePAllocator("Swapchain"));
        vkDestroySurfaceKHR(s_RendererData.instance,s_RendererData.surface,CreatePAllocator("Surface"));
        vkDestroyDevice(s_RendererData.device,CreatePAllocator("Device"));
        vkDestroyInstance(s_RendererData.instance,CreatePAllocator("Instance"));
    }
}