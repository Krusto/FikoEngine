//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once

#include <vulkan/vulkan.h>
#include <Core/Core.h>
#include <Renderer/Vertex.h>
#include <Renderer/VertexArray.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexLayout.h>
#include <Renderer/Vulkan/Buffer.h>

namespace FikoEngine {

    class VulkanVertexBuffer : public VertexBuffer {
    public:
<<<<<<< HEAD
        VulkanVertexBuffer(const VertexLayout &layout, float *data, uint32_t length);
        VulkanVertexBuffer(const VertexLayout &layout, Vertex *data, uint32_t length);

        virtual void Bind() const override;
    private:
        Buffer m_Buffer;
        uint32_t m_Length;
=======
        VulkanVertexBuffer(const VertexLayout &layout, float *data, u32 length);
        VulkanVertexBuffer(const VertexLayout &layout, Vertex *data, u32 length);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

        virtual void Bind() const override;
    private:
        Buffer m_Buffer;
        u32 m_Length;
    };
    Buffer CreateVertexBuffer(VkPhysicalDevice physicalDevice,
                              VkDevice device,
                              VkAllocationCallbacks* allocator,
                              VkQueue graphicsQueue,
                              VkCommandPool commandPool,
                              Vertex* data,
                              VertexLayout vertexLayout,
                              u32 vertexCount);

}