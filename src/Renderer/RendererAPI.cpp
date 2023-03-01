//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include "RendererAPI.h"
#include "Window.h"

#include "Vulkan/VulkanRenderer.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"
#include "Vulkan/Device.h"
#include "Vulkan/Swapchain.h"
#include "Vulkan/RendererData.h"
#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/Renderpass.h"
#include "Vulkan/Memory.h"
#include "Vulkan/Command.h"
#include "Vulkan/Synchronization.h"
#include "Vulkan/Queue.h"
#include "Renderer.h"
#include "Vertex.h"
#include "Renderer/Vulkan/Framebuffer.h"
#include "Renderer/Vulkan/Material.h"
#include <Scene/Entity.h>

namespace FikoEngine {

/*
    void RendererAPI::ResizeFramebuffer(ViewportSize size) {
        VulkanRenderer::s_RendererData.framebufferResized = false;
        VulkanRenderer::s_RendererData.swapchainSpec.imageExtent = VkExtent2D{size.width,size.height};
        VulkanRenderer::s_RendererData.swapchainSpec.frameSize = ViewportSize{size.width,size.height};

        VulkanRenderer::s_RendererData.swapchain->Recreate();

        vkDestroyRenderPass(VulkanRenderer::s_RendererData.device,VulkanRenderer::s_RendererData.renderPass,nullptr);
        VulkanRenderer::s_RendererData.renderPass = CreateRenderPass(VulkanRenderer::s_RendererData.swapchainSpec);

        VulkanRenderer::s_RendererData.framebuffer->Resize(size.width,size.height);
    }

    void RendererAPI::InitImGUI() {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanRenderer::InitImGUI();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::SetActiveWindow(Window *window) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanRenderer::s_RendererData.window = window->getHandle();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::AddMaterial(Ref<Material> material) {
        RendererAPI::s_Materials.try_emplace(material->GetName(),material);
    }
*/

}