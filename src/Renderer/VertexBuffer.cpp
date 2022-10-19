#include "VertexBuffer.h"
#include <Renderer/RendererApi.h>
#include <Renderer/OpenGL/OpenGLVertexBuffer.h>
Ref<VertexBuffer> VertexBuffer::Create(Ref<VertexArray> va, const VertexLayout& layout, Vertex* data, uint32_t length) {
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        return Ref<OpenGLVertexBuffer>::Create(va, layout, data, length);
        break;
    default:
        exit(-1);
        break;
    }
}
Ref<VertexBuffer> VertexBuffer::Create(Ref<VertexArray> va, const VertexLayout& layout, float* data, uint32_t length) {
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        return Ref<OpenGLVertexBuffer>::Create(va, layout, data, length);
        break;
    default:
        exit(-1);
        break;
    }
}