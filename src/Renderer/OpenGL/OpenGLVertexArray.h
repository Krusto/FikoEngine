#pragma once
#include <cstdint>
#include <Renderer/VertexArray.h>
namespace FikoEngine {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray() = default;

        explicit OpenGLVertexArray(u32 indexCount);

        static OpenGLVertexArray Create(u32 indexCount);

        void Bind() const override;

        void Unbind() const override;
    };
}