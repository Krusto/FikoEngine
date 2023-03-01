#pragma once
#include <cstdint>
#include <Renderer/VertexArray.h>
class OpenGLVertexArray : public VertexArray{
public:
    OpenGLVertexArray()=default;
    explicit OpenGLVertexArray(uint32_t indexCount);
    static OpenGLVertexArray Create(uint32_t indexCount);
    void Bind() const override;
    void Unbind() const override;
};
