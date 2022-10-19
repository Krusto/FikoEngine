#include "VertexArray.h"
#include <Renderer/RendererAPI.h>

namespace FikoEngine {

    Ref<VertexArray> VertexArray::Create(uint32_t indexCount) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLVertexArray>::Create(indexCount);
            default:
                break;
        }
    }
}