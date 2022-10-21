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
        VulkanIndexBuffer(Ref<VertexArray> va, const uint32_t *data, uint32_t length);

        virtual void Bind() const override;

    };

    Buffer CreateIndexBuffer(VkPhysicalDevice physicalDevice,
                             VkDevice device,
                             VkAllocationCallbacks* allocator,
                             VkQueue graphicsQueue,
                             VkCommandPool commandPool,
                             u32* data,
                             u32 count);
}