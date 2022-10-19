#include "IndexBuffer.h"
#include <Core/Ref.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/OpenGL/OpenGLIndexBuffer.h>

namespace FikoEngine {

    Ref<IndexBuffer> IndexBuffer::Create(Ref<VertexArray> va, const uint32_t *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLIndexBuffer>::Create(va, data, length);
                break;
            default:
                assert(0);
                break;
        }
        assert(0);
        return {};
    }
}