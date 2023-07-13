#pragma once
#include <cstdint>
#include <Core/Ref.h>
#include <Renderer/Vertex.h>

namespace FikoEngine {
    class VertexBuffer : public RefCounted {
    public:
        virtual ~VertexBuffer() {};

        static Ref<VertexBuffer> Create(const VertexLayout &layout, Vertex *data, uint32_t length);
        static Ref<VertexBuffer> Create(const VertexLayout &layout, float *data, uint32_t length);

        uint32_t GetID() const { return m_ID; }

        virtual void Bind() const = 0;

        virtual size_t GetSize() const = 0;
    protected:
        uint32_t m_ID;
    };
}