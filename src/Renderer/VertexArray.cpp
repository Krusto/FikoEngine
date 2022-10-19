#include "VertexArray.h"
#include <Renderer/RendererApi.h>
#include <Renderer/OpenGL/OpenGLVertexArray.h>
Ref<VertexArray> VertexArray::Create(uint32_t indexCount) {
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        return Ref<OpenGLVertexArray>::Create(indexCount);
    default:
        break;
    }
}
