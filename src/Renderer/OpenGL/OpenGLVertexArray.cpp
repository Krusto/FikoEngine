#include <glad/glad.h>
#include <cassert>
#include "OpenGLVertexArray.h"
namespace FikoEngine {

    OpenGLVertexArray::OpenGLVertexArray(u32 indexCount) {
        glGenVertexArrays(1, &m_ID);
        this->IndexCount = indexCount;
    }

    void OpenGLVertexArray::Bind() const {
        assert(m_ID != 0);
        glBindVertexArray(m_ID);
    }

    OpenGLVertexArray OpenGLVertexArray::Create(u32 indexCount) {
        return OpenGLVertexArray(indexCount);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }
}