#pragma once
#include <cstdint>
#include <Renderer/VertexArray.h>
namespace FikoEngine {
    class VulkanVertexArray : public VertexArray {
    public:
        VulkanVertexArray() = default;

        explicit VulkanVertexArray(uint32_t indexCount);

        static VulkanVertexArray Create(uint32_t indexCount);

        void Bind() const override;

        void Unbind() const override;
    };
}