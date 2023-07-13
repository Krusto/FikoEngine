//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <vulkan/vulkan.h>
#include "../VertexLayout.h"

namespace FikoEngine{

    enum class BufferType{
        None,
        Vertex,
        Index,
        Staging,
        Uniform
    };

    class Buffer{
    public:
        Buffer() = default;
        Buffer(const Buffer&) = default;
        Buffer(VkBuffer buffer,BufferType type,VkDeviceMemory memory,uint32_t size,uint32_t length)
            :buffer(buffer),type(type),memory(memory),length(length),size(size){}

    public:
        static Buffer Create(VkPhysicalDevice physicalDevice,VkDevice device,VkAllocationCallbacks* allocationCallbacks,uint32_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
        static void Copy(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src,Buffer dst,uint32_t size);
        static uint32_t FindMemoryType(VkPhysicalDevice physicalDevice,uint32_t typeFilter, VkMemoryPropertyFlags properties);
        static void CopyBuffer(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src,Buffer dst,uint32_t size);
        void Destroy(VkDevice device,VkAllocationCallbacks* callbacks);

    public:
        Buffer& operator =(const Buffer& rhs) = default;
        operator VkBuffer(){return buffer;}

    public:
        VkBuffer buffer{};
        BufferType type{};
        VkDeviceMemory memory{};
        uint32_t length{};
        uint32_t size{};
    };

}