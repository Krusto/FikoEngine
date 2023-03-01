#include <glad/glad.h>
#include <cassert>
#include "OpenGLVertexArray.h"
namespace FikoEngine {

    OpenGLVertexArray::OpenGLVertexArray(uint32_t indexCount) {
        glGenVertexArrays(1, &m_ID);
        this->IndexCount = indexCount;
    }

    void OpenGLVertexArray::Bind() const {
        assert(m_ID != 0);
        glBindVertexArray(m_ID);
    }

    OpenGLVertexArray OpenGLVertexArray::Create(uint32_t indexCount) {
        return OpenGLVertexArray(indexCount);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }
}