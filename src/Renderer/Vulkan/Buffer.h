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
        Buffer(VkBuffer buffer,BufferType type,VkDeviceMemory memory,u32 size,u32 length)
            :buffer(buffer),type(type),memory(memory),size(size),length(length){}

    public:
        static Buffer Create(VkPhysicalDevice physicalDevice,VkDevice device,VkAllocationCallbacks* allocationCallbacks,u32 size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
        static void Copy(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src,Buffer dst,u32 size);
        static u32 FindMemoryType(VkPhysicalDevice physicalDevice,u32 typeFilter, VkMemoryPropertyFlags properties);
        static void CopyBuffer(VkDevice device,VkCommandPool commandPool,VkQueue queue,Buffer src,Buffer dst,u32 size);
        void Destroy(VkDevice device,VkAllocationCallbacks* callbacks);

    public:
        Buffer& operator =(const Buffer& rhs) = default;
        operator VkBuffer(){return buffer;}

    public:
        VkBuffer buffer{};
        BufferType type{};
        VkDeviceMemory memory{};
        u32 length{};
        u32 size{};
    };

}