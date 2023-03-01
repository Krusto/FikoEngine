#pragma once

#include <Renderer/VertexArray.h>
#include <Renderer/IndexBuffer.h>
#include <cstdint>

class OpenGLIndexBuffer : public IndexBuffer{
public:
    OpenGLIndexBuffer()=default;
    OpenGLIndexBuffer(Ref<VertexArray> va,const uint32_t* data, uint32_t length);
    static OpenGLIndexBuffer Create(Ref<VertexArray> va,const uint32_t* data, uint32_t length);
    void Bind() const override;

private:
};