//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include <vulkan/vulkan.h>
#include "RendererAPI.h"
#include "Window.h"
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
#include "Vertex.h"
#include "Vulkan/VertexBuffer.h"
#include "Vulkan/IndexBuffer.h"
#include "Vulkan/UniformBuffer.h"
#include "Vulkan/DescriptorSet.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace FikoEngine 
{
    inline RendererDataAPI s_RendererData;

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) 
    {
        s_RendererData.workingDir = applicationSpec.WorkingDirectory;
        s_RendererData.allocator = CreatePAllocator("Allocator");
        s_RendererData.instance = CreateInstance(&s_RendererData,applicationSpec);
        s_RendererData.physicalDevice = SelectPhysicalDevice(&s_RendererData);
        rendererSpec.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        s_RendererData.device = CreateDevice(&s_RendererData,rendererSpec.extensions);
        s_RendererData.surface = applicationSpec.window->CreateSurface(s_RendererData.instance);
        s_RendererData.framebufferSize = rendererSpec.SurfaceSize;

        s_RendererData.shaders.emplace_back("assets/flat3D");
        s_RendererData.selectedShader = s_RendererData.shaders[s_RendererData.selectedShaderID];
        s_RendererData.descriptorSetLayout = CreateDescriptorSetLayout(&s_RendererData);
        SwapchainRecreate(&s_RendererData,rendererSpec.SurfaceSize,s_RendererData.selectedShader.c_str());

        s_RendererData.commandPool = CreateCommandPool(&s_RendererData);

        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.graphicsQueue);
        vkGetDeviceQueue(s_RendererData.device, s_RendererData.queueFamilyIndex, 0, &s_RendererData.presentQueue);

        std::vector<Vertex> vertices = {
                {{-0.5f, -0.5f,0.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f,0.0f}, {0.0f, 1.0f, 0.0f}},
                {{0.5f, 0.5f,0.0f}, {0.0f, 0.0f, 1.0f}},
                {{-0.5f, 0.5f,0.0f}, {1.0f, 1.0f, 1.0f}}
        };
        
        std::vector<u32> indices = {0,1,2,2,3,0};
        s_RendererData.vertexBuffer = CreateVertexBuffer(&s_RendererData,vertices.data(),Vertex::GetLayout(),vertices.size());
        s_RendererData.indexBuffer = CreateIndexBuffer(&s_RendererData,indices.data(),indices.size());
        s_RendererData.uniformBuffers = CreateUniformBuffers(&s_RendererData,MVPUniform::GetLayout(),s_RendererData.maxFramesInFlight);

        s_RendererData.descriptorPool = CreateDescriptorPool(&s_RendererData);
        s_RendererData.descriptorSets = CreateDescriptorSets(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.commandBuffers = CreateCommandBuffers(&s_RendererData,s_RendererData.imageViews.size());

        s_RendererData.imageAvailableSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.renderFinishedSemaphores = CreateSemaphores(&s_RendererData,s_RendererData.maxFramesInFlight);
        s_RendererData.inFlightFences = CreateFences(&s_RendererData,s_RendererData.maxFramesInFlight);

        LOG("Renderer initialized!");

    }
    
    void RendererAPI::Update()
    {
        s_RendererData.selectedShader = s_RendererData.shaders[s_RendererData.selectedShaderID];
    }
    
    void RendererAPI::Draw() 
    {
        WaitFence(&s_RendererData, s_RendererData.currentImageIndex);

        u32 imageIndex;
        VkResult result;

        result = SwapchainAcquireNextImage(&s_RendererData, imageIndex, s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) 
        {
            SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.selectedShader.c_str());
        }

        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        MVPUniform ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.projection = glm::perspective(glm::radians(45.0f), s_RendererData.framebufferSize.x / (float) s_RendererData.framebufferSize.y, 0.1f, 10.0f);
        ubo.projection[1][1] *= -1;

        void* data;
        vkMapMemory(s_RendererData.device, s_RendererData.uniformBuffers[s_RendererData.currentImageIndex].memory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(s_RendererData.device, s_RendererData.uniformBuffers[s_RendererData.currentImageIndex].memory);


        ResetFence(&s_RendererData, s_RendererData.currentImageIndex);

        ResetCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);

        BeginCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);
        BeginRenderPass(&s_RendererData, s_RendererData.currentImageIndex);

        BindGraphicsPipeline(&s_RendererData, s_RendererData.currentImageIndex);
        GraphicsPipelineDrawIndexedU(&s_RendererData,s_RendererData.vertexBuffer,
                                     s_RendererData.indexBuffer,
                                     s_RendererData.uniformBuffers[s_RendererData.currentImageIndex],
                                     s_RendererData.currentImageIndex);

        EndRenderPass(&s_RendererData, s_RendererData.currentImageIndex);
        EndCommandBuffer(&s_RendererData, s_RendererData.currentImageIndex);

        QueueSubmit(&s_RendererData, s_RendererData.currentImageIndex);

        result = QueuePresent(&s_RendererData, imageIndex, s_RendererData.currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || s_RendererData.framebufferResized) 
        {
            SwapchainRecreate(&s_RendererData, s_RendererData.framebufferSize, s_RendererData.selectedShader.c_str());
            s_RendererData.framebufferResized = 0;
        }

        s_RendererData.currentImageIndex = (s_RendererData.currentImageIndex + 1) % s_RendererData.maxFramesInFlight;
    }
    
    void RendererAPI::Destroy()
    {
        vkDeviceWaitIdle(s_RendererData.device);

        for (u32 i = 0; i < s_RendererData.maxFramesInFlight; ++i) 
        {
            vkDestroySemaphore(s_RendererData.device,s_RendererData.imageAvailableSemaphores[i],s_RendererData.allocator);
            vkDestroySemaphore(s_RendererData.device,s_RendererData.renderFinishedSemaphores[i],s_RendererData.allocator);
            vkDestroyFence(s_RendererData.device,s_RendererData.inFlightFences[i],s_RendererData.allocator);
        }
        vkDestroyCommandPool(s_RendererData.device,s_RendererData.commandPool, s_RendererData.allocator);
        SwapchainCleanup(&s_RendererData);

        vkDestroyBuffer(s_RendererData.device,s_RendererData.vertexBuffer.buffer,s_RendererData.allocator);
        vkFreeMemory(s_RendererData.device,s_RendererData.vertexBuffer.memory,s_RendererData.allocator);
        vkDestroyBuffer(s_RendererData.device,s_RendererData.indexBuffer.buffer,s_RendererData.allocator);
        vkFreeMemory(s_RendererData.device,s_RendererData.indexBuffer.memory,s_RendererData.allocator);

        vkDestroySurfaceKHR(s_RendererData.instance,s_RendererData.surface,nullptr);
        vkDestroyDevice(s_RendererData.device,s_RendererData.allocator);
        DestroyDebugUtilsMessengerEXT(s_RendererData.instance,s_RendererData.debug,s_RendererData.allocator);
        vkDestroyInstance(s_RendererData.instance,s_RendererData.allocator);
    }

    void RendererAPI::ResizeFramebuffer(Extent2D size) 
    {
        s_RendererData.framebufferResized = true;
        s_RendererData.framebufferSize = size;
    }

}
