
#include <glad/glad.h>
#include <cassert>
#include "OpenGLIndexBuffer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(Ref<VertexArray> va,const uint32_t*data, uint32_t length) {
    va->Bind();
    glGenBuffers(1,&m_ID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*length,data, GL_STATIC_DRAW);

    indexCount = length;
}

void OpenGLIndexBuffer::Bind() const {
    assert(m_ID != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ID);
}

OpenGLIndexBuffer OpenGLIndexBuffer::Create(Ref<VertexArray> va, const uint32_t* data, uint32_t length) {
    return OpenGLIndexBuffer{va,data,length};
}

