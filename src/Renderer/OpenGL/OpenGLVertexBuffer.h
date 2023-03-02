#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexLayout.h>
#include <Renderer/Vertex.h>

namespace FikoEngine {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer() = default;

        OpenGLVertexBuffer(const VertexLayout &layout, float *data, u32 length);

        OpenGLVertexBuffer(const VertexLayout &layout, Vertex *data, u32 length);

        static OpenGLVertexBuffer Create(const VertexLayout &layout, float *data, u32 length);

        static OpenGLVertexBuffer Create(const VertexLayout &layout, Vertex *data, u32 length);

        u32 GetID() const { return m_ID; }

        void Bind() const;

    private:
        u32 m_ID{};
    };
}