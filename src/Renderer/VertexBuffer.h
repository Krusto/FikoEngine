#pragma once
#include <cstdint>
#include <Core/Ref.h>
#include <Renderer/Vertex.h>

namespace FikoEngine {
    class VertexBuffer : public RefCounted {
    public:
        static Ref<VertexBuffer> Create(const VertexLayout &layout, Vertex *data, u32 length);

        static Ref<VertexBuffer> Create(const VertexLayout &layout, float *data, u32 length);

        u32 GetID() const { return m_ID; }

        virtual void Bind() const = 0;

    protected:
        u32 m_ID;
    };
}