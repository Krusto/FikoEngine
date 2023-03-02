#pragma once

#include <Renderer/VertexArray.h>
#include <Renderer/IndexBuffer.h>
#include <cstdint>

namespace FikoEngine {
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer() = default;

        OpenGLIndexBuffer(const u32 *data, u32 length);

        static OpenGLIndexBuffer Create(const u32 *data, u32 length);

        void Bind() const override;

    private:
    };
}