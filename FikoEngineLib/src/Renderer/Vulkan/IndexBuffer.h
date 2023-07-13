//
// Created by Stoyanov, Krusto (K.S.) on 6/25/2022.
//
#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"
#include <Renderer/VertexLayout.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/VertexArray.h>
#include <Core/Core.h>

namespace FikoEngine {

    class VulkanIndexBuffer : public IndexBuffer{
    public:
        VulkanIndexBuffer(const uint32_t *data, uint32_t length);

        ~VulkanIndexBuffer() = default;

        virtual void Bind() const override;
    private:
        Buffer m_Buffer;
        uint32_t m_Length;
    };

    Buffer CreateIndexBuffer(VkPhysicalDevice physicalDevice,
                             VkDevice device,
                             VkAllocationCallbacks* allocator,
                             VkQueue graphicsQueue,
                             VkCommandPool commandPool,
                             const uint32_t* data,
                             uint32_t count);
}