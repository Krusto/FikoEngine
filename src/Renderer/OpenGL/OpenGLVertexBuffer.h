#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexLayout.h>
#include <Renderer/Vertex.h>

class OpenGLVertexBuffer : public VertexBuffer{
public:
    OpenGLVertexBuffer() = default;
    OpenGLVertexBuffer(Ref<VertexArray> va,const VertexLayout& layout,float* data,uint32_t length);
    OpenGLVertexBuffer(Ref<VertexArray> va,const VertexLayout& layout,Vertex* data,uint32_t length);

    static OpenGLVertexBuffer Create(Ref<VertexArray> va,const VertexLayout& layout,float* data, uint32_t length);
    static OpenGLVertexBuffer Create(Ref<VertexArray> va,const VertexLayout& layout,Vertex* data, uint32_t length);
    [[nodiscard]] uint32_t GetID() const{return m_ID;}

    void Bind() const;

private:
    uint32_t m_ID{};
};