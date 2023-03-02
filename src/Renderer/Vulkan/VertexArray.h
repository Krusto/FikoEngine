#pragma once
#include <cstdint>
#include <Renderer/VertexArray.h>
namespace FikoEngine {
    class VulkanVertexArray : public VertexArray {
    public:
        VulkanVertexArray() = default;

        VulkanVertexArray(u32 indexCount);

        static VulkanVertexArray Create(u32 indexCount);

        void Bind() const override;

        void Unbind() const override;
    };
}