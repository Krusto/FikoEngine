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
        VulkanVertexBuffer(Ref<VertexArray> va, const VertexLayout &layout, float *data, uint32_t length);
        VulkanVertexBuffer(Ref<VertexArray> va, const VertexLayout &layout, Vertex *data, uint32_t length);

        virtual void Bind() const override{};

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