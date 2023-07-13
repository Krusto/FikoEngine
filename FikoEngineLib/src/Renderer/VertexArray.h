#pragma once
#include <cstdint>
#include <Core/Ref.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace FikoEngine {

    class VertexArray : public RefCounted {
    public:
        static Ref<VertexArray> Create(uint32_t indexCount);

        virtual ~VertexArray() {};

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        unsigned int IndexCount{};

        uint32_t id() { return m_ID; }

        void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer);
        void AddIndexBuffer(Ref<IndexBuffer> indexBuffer);
    protected:
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        uint32_t m_ID{};
    };
}