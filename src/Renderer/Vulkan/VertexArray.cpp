#include <cassert>
#include "VertexArray.h"

namespace FikoEngine {

    VulkanVertexArray::VulkanVertexArray(uint32_t indexCount) {
        this->IndexCount = indexCount;
    }

    void VulkanVertexArray::Bind() const {
        assert(m_ID != 0);
    }

    VulkanVertexArray VulkanVertexArray::Create(uint32_t indexCount) {
        return VulkanVertexArray(indexCount);
    }

    void VulkanVertexArray::Unbind() const {
    }
}