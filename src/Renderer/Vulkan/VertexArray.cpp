#include <cassert>
#include "VertexArray.h"
#include "Core/UUID.h"

namespace FikoEngine {

    VulkanVertexArray::VulkanVertexArray(u32 indexCount) {
        this->IndexCount = indexCount;
        m_ID = UUID();
    }

    void VulkanVertexArray::Bind() const {
        assert(m_ID != 0);
        if(m_VertexBuffer)
            m_VertexBuffer->Bind();
        if(m_IndexBuffer)
            m_IndexBuffer->Bind();
    }

    VulkanVertexArray VulkanVertexArray::Create(u32 indexCount) {
        return VulkanVertexArray(indexCount);
    }

    void VulkanVertexArray::Unbind() const {
    }
}