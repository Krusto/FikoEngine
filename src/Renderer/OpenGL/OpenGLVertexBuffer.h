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

        OpenGLVertexBuffer(const VertexLayout &layout, float *data, uint32_t length);

        OpenGLVertexBuffer(const VertexLayout &layout, Vertex *data, uint32_t length);

        static OpenGLVertexBuffer Create(const VertexLayout &layout, float *data, uint32_t length);

        static OpenGLVertexBuffer Create(const VertexLayout &layout, Vertex *data, uint32_t length);

        uint32_t GetID() const { return m_ID; }

        void Bind() const;

    private:
        uint32_t m_ID{};
    };
}