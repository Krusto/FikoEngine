//
// Created by Stoyanov, Krusto (K.S.) on 6/25/2022.
//
#include "IndexBuffer.h"
#include "VulkanRenderer.h"

namespace FikoEngine{

    VulkanIndexBuffer::VulkanIndexBuffer(const uint32_t *data, uint32_t length) {
        m_Length = length;
        m_Buffer = CreateIndexBuffer(VulkanRenderer::s_RendererData.physicalDevice,
                                     VulkanRenderer::s_RendererData.device,
                                     nullptr,
                                     VulkanRenderer::s_RendererData.graphicsQueue,
                                     VulkanRenderer::s_RendererData.commandPool,
                                     data,
                                     length);
    }

    void VulkanIndexBuffer::Bind() const {
        vkCmdBindIndexBuffer(VulkanRenderer::s_RendererData.commandBuffers[VulkanRenderer::s_RendererData.currentFrameIndex],
                             m_Buffer.buffer,
                             0,
                             VK_INDEX_TYPE_UINT32);
    }

    Buffer CreateIndexBuffer(VkPhysicalDevice physicalDevice,
                             VkDevice device,
                             VkAllocationCallbacks* allocator,
                             VkQueue graphicsQueue,
                             VkCommandPool commandPool,
                             const uint32_t* data,
                             uint32_t count) {
        uint32_t bufferSize = sizeof(uint32_t) * count;
        Buffer stagingBuffer = Buffer::Create(physicalDevice,
                                              device,
                                              allocator,
                                              bufferSize,
                                              VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        stagingBuffer.type = BufferType::Staging;
        stagingBuffer.length = count;
        stagingBuffer.size = bufferSize;

        void* _data{};
        vkMapMemory(device, stagingBuffer.memory, 0, bufferSize, 0, &_data);
        memcpy(_data, data, (size_t) bufferSize);
        vkUnmapMemory(device, stagingBuffer.memory);

        Buffer indexBuffer = Buffer::Create(physicalDevice,
                                             device,
                                             allocator,
                                             bufferSize,
                                             VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        indexBuffer.type = BufferType::Index;
        indexBuffer.size = bufferSize;
        indexBuffer.length = count;

        Buffer::Copy(device,commandPool,graphicsQueue,stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(device, stagingBuffer.buffer, allocator);
        vkFreeMemory(device, stagingBuffer.memory, allocator);

        return indexBuffer;
    }
}