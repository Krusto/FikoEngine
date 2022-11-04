//
// Created by Stoyanov, Krusto (K.S.) on 6/24/2022.
//
#include"VertexBuffer.h"
#include "VulkanContext.h"

namespace FikoEngine{

Buffer CreateVertexBuffer(VkPhysicalDevice physicalDevice,
                          VkDevice device,
                          VkAllocationCallbacks* allocator,
                          VkQueue graphicsQueue,
                          VkCommandPool commandPool,
                          Vertex* data,
                          VertexLayout vertexLayout,
                          u32 vertexCount) {
    u32 bufferSize = vertexLayout.stride * vertexCount;
    Buffer stagingBuffer = Buffer::Create(physicalDevice,
                                          device,
                                          allocator,
                                          bufferSize,
                                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    stagingBuffer.type = BufferType::Staging;
    stagingBuffer.length = vertexCount;
    stagingBuffer.size = bufferSize;

    void* _data{};
    vkMapMemory(device, stagingBuffer.memory, 0, bufferSize, 0, &_data);
    memcpy(_data, data, (size_t) bufferSize);
    vkUnmapMemory(device, stagingBuffer.memory);

    Buffer vertexBuffer = Buffer::Create(physicalDevice,
                                         device,
                                         allocator,
                                         bufferSize,
                                         VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vertexBuffer.type = BufferType::Vertex;
    vertexBuffer.length = vertexCount;
    vertexBuffer.size = bufferSize;

    Buffer::Copy(device,commandPool,graphicsQueue,stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(device, stagingBuffer.buffer, allocator);
    vkFreeMemory(device, stagingBuffer.memory, allocator);

    return vertexBuffer;
}

    VulkanVertexBuffer::VulkanVertexBuffer(const VertexLayout &layout, float *data,
                                           uint32_t length) {
        m_Buffer = CreateVertexBuffer(VulkanContext::s_RendererData.physicalDevice,
                                      VulkanContext::s_RendererData.device,
                                      nullptr,
                                      VulkanContext::s_RendererData.graphicsQueue,
                                      VulkanContext::s_RendererData.commandPool,
                                      (Vertex*)data,
                                      layout,
                                      length);
        m_Length = length;
    }

    VulkanVertexBuffer::VulkanVertexBuffer(const VertexLayout &layout, Vertex *data,
                                           uint32_t length) {
        m_Buffer = CreateVertexBuffer(VulkanContext::s_RendererData.physicalDevice,
                                      VulkanContext::s_RendererData.device,
                                      nullptr,
                                      VulkanContext::s_RendererData.graphicsQueue,
                                      VulkanContext::s_RendererData.commandPool,
                                      data,
                                      layout,
                                      length);
        m_Length = length;
    }

    void VulkanVertexBuffer::Bind() const {
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(
                VulkanContext::s_RendererData.commandBuffers[VulkanContext::s_RendererData.currentFrameIndex],
                0,
                1,
                &m_Buffer.buffer,
                offsets);
    }
}