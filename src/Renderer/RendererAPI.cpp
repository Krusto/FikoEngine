//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include "RendererAPI.h"
#include "Window.h"

#include "Vulkan/VulkanContext.h"
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

    void RendererAPI::Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::Init(rendererSpec,applicationSpec);
                break;
            default:
                exit(-1);
                break;
        }

        LOG("Renderer initialized!");
    }
    void RendererAPI::Draw(Entity entity) {
        WaitFence(VulkanContext::s_RendererData.inFlightFences,VulkanContext::s_RendererData.currentFrameIndex);

        uint32_t imageIndex;
        VkResult result = SwapchainAcquireNextImage(VulkanContext::s_RendererData.swapchain,
                                           VulkanContext::s_RendererData.imageAvailableSemaphores[VulkanContext::s_RendererData.currentFrameIndex],
                                           imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            uint32_t width,height;
            glfwGetWindowSize(VulkanContext::s_RendererData.window,(int*)&width,(int*)&height);
            RendererAPI::ResizeFramebuffer(ViewportSize{width,height});

        }else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        if(true){ //record command buffer
            BeginCommandBuffer(VulkanContext::s_RendererData.commandBuffers,
                               VulkanContext::s_RendererData.currentFrameIndex);

            auto &swapchain = VulkanContext::s_RendererData.swapchain;

            BeginRenderPass(VulkanContext::s_RendererData.commandBuffers,
                            swapchain,
                            imageIndex);

            if(entity.IsValid() && entity.HasComponent<MaterialComponent>()) {
                auto va = entity.GetComponent<MeshComponent>().GetVA();
                auto virtualMaterial = entity.GetComponent<MaterialComponent>().material;
                auto vulkanMaterial = static_cast<Ref<VulkanMaterial>>(virtualMaterial);
                auto vulkanShader = static_cast<Ref<VulkanShader>>(vulkanMaterial->GetShader());

                BindGraphicsPipeline(VulkanContext::s_RendererData.commandBuffers,
                                     vulkanShader,
                                     VulkanContext::s_RendererData.currentFrameIndex);

                VkViewport viewport{};
                viewport.x = 0.0f;
                viewport.y = 0.0f;
                viewport.width = (float) swapchain->GetSwapchainSpec().frameSize.width;
                viewport.height = (float) swapchain->GetSwapchainSpec().frameSize.height;
                viewport.minDepth = 0.0f;
                viewport.maxDepth = 1.0f;
                vkCmdSetViewport(
                        VulkanContext::s_RendererData.commandBuffers[VulkanContext::s_RendererData.currentFrameIndex],
                        0, 1, &viewport);

                VkRect2D scissor{};
                scissor.offset = {0, 0};
                scissor.extent = swapchain->GetSwapchainSpec().imageExtent;
                vkCmdSetScissor(
                        VulkanContext::s_RendererData.commandBuffers[VulkanContext::s_RendererData.currentFrameIndex],
                        0, 1, &scissor);


                va->Bind();
                GraphicsPipelineDrawIndexed(VulkanContext::s_RendererData.commandBuffers,
                                            VulkanContext::s_RendererData.currentFrameIndex,
                                            va->IndexCount);

                //GraphicsPipelineDraw(VulkanContext::s_RendererData.commandBuffers,
                //                     VulkanContext::s_RendererData.currentFrameIndex);
            }
            EndRenderPass(VulkanContext::s_RendererData.commandBuffers,
                          VulkanContext::s_RendererData.currentFrameIndex);

            EndCommandBuffer(VulkanContext::s_RendererData.commandBuffers,
                             VulkanContext::s_RendererData.currentFrameIndex);

        }

        ResetFence(VulkanContext::s_RendererData.inFlightFences, VulkanContext::s_RendererData.currentFrameIndex);

        QueueSubmit(VulkanContext::s_RendererData.graphicsQueue,
                    VulkanContext::s_RendererData.imageAvailableSemaphores,
                    VulkanContext::s_RendererData.renderFinishedSemaphores,
                    VulkanContext::s_RendererData.inFlightFences,
                    VulkanContext::s_RendererData.currentFrameIndex);

        result = QueuePresent(VulkanContext::s_RendererData.graphicsQueue,
                              VulkanContext::s_RendererData.swapchain,
                              VulkanContext::s_RendererData.renderFinishedSemaphores,
                              VulkanContext::s_RendererData.inFlightFences,
                              imageIndex,
                              VulkanContext::s_RendererData.currentFrameIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || VulkanContext::s_RendererData.framebufferResized) {
            uint32_t width,height;
            glfwGetWindowSize(VulkanContext::s_RendererData.window,(int*)&width,(int*)&height);
            RendererAPI::ResizeFramebuffer(ViewportSize{width,height});
        }

        VulkanContext::s_RendererData.currentFrameIndex = (VulkanContext::s_RendererData.currentFrameIndex + 1) % VulkanContext::s_RendererData.maxFramesInFlight;
    }
    void RendererAPI::Destroy(){
        vkDeviceWaitIdle(VulkanContext::s_RendererData.device);

        for (u32 i = 0; i < VulkanContext::s_RendererData.maxFramesInFlight; ++i) {
            vkDestroySemaphore(VulkanContext::s_RendererData.device,VulkanContext::s_RendererData.imageAvailableSemaphores[i],nullptr);
            vkDestroySemaphore(VulkanContext::s_RendererData.device,VulkanContext::s_RendererData.renderFinishedSemaphores[i],nullptr);
            vkDestroyFence(VulkanContext::s_RendererData.device,VulkanContext::s_RendererData.inFlightFences[i],nullptr);
        }
        vkDestroyCommandPool(VulkanContext::s_RendererData.device,VulkanContext::s_RendererData.commandPool, nullptr);

        VulkanContext::s_RendererData.swapchain->Cleanup();

        vkDestroySurfaceKHR(VulkanContext::s_RendererData.instance,VulkanContext::s_RendererData.surface,nullptr);
        vkDestroyDevice(VulkanContext::s_RendererData.device,nullptr);
        DestroyDebugUtilsMessengerEXT(VulkanContext::s_RendererData.instance,VulkanContext::s_RendererData.debug,nullptr);
        vkDestroyInstance(VulkanContext::s_RendererData.instance,nullptr);
    }

    void RendererAPI::ResizeFramebuffer(ViewportSize size) {
        VulkanContext::s_RendererData.framebufferResized = false;
        VulkanContext::s_RendererData.swapchainSpec.imageExtent = VkExtent2D{size.width,size.height};
        VulkanContext::s_RendererData.swapchainSpec.frameSize = ViewportSize{size.width,size.height};

        VulkanContext::s_RendererData.swapchain->Recreate();

        vkDestroyRenderPass(VulkanContext::s_RendererData.device,VulkanContext::s_RendererData.renderPass,nullptr);
        VulkanContext::s_RendererData.renderPass = CreateRenderPass(VulkanContext::s_RendererData.swapchainSpec);

        VulkanContext::s_RendererData.framebuffer->Resize(size.width,size.height);
    }

    void RendererAPI::ClearColor(glm::vec4 color) {
        //TODO
    }

    void RendererAPI::InitImGUI() {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::InitImGUI();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::SetActiveWindow(Window *window) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                VulkanContext::s_RendererData.window = window->getHandle();
                break;
            default:
                exit(-1);
                break;
        }
    }

    void RendererAPI::AddMaterial(Ref<Material> material) {
        RendererAPI::s_Materials.try_emplace(material->GetName(),material);
    }

}