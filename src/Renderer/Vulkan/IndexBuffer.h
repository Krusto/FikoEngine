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
<<<<<<< HEAD
        VulkanIndexBuffer(const uint32_t *data, uint32_t length);
=======
        VulkanIndexBuffer(const u32 *data, u32 length);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

        virtual void Bind() const override;
    private:
        Buffer m_Buffer;
        u32 m_Length;
    };

    Buffer CreateIndexBuffer(VkPhysicalDevice physicalDevice,
                             VkDevice device,
                             VkAllocationCallbacks* allocator,
                             VkQueue graphicsQueue,
                             VkCommandPool commandPool,
                             const u32* data,
                             u32 count);
}