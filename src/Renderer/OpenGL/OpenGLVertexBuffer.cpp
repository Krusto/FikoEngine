#include <glad/glad.h>


#include "OpenGLVertexBuffer.h"

#include <utility>
#include <cassert>
namespace FikoEngine {

    OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexLayout &layout, float *data,
                                           u32 length) {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, length * layout.stride, data, GL_STATIC_DRAW);

        u32 index = 0;
        u32 offset = 0;

        glVertexAttribPointer(index, 3, GL_FLOAT, 0, 32, reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(index);
        index++;

        glVertexAttribPointer(index, 3, GL_FLOAT, 0, 32, reinterpret_cast<void *>(12));
        glEnableVertexAttribArray(index);
        index++;

        glVertexAttribPointer(index, 2, GL_FLOAT, 0, 32, reinterpret_cast<void *>(24));
        glEnableVertexAttribArray(index);
        index++;
        /* for (auto attr : layout.attributes) {
             if (attr.second.type != "int1") {
                 glVertexAttribPointer(index, attr.first / sizeof(float), GL_FLOAT, 0, layout.stride, reinterpret_cast<void*>(offset));
             }
             else {
                 glVertexAttribPointer(index, attr.first / sizeof(int32_t), GL_INT, 0, layout.stride, reinterpret_cast<void*>(offset));
             }
             glEnableVertexAttribArray(index);
             index++;
             offset += attr.first;
         }*/
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexLayout &layout, Vertex *data,
                                           u32 length) {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, length * layout.stride, (void *) data, GL_STATIC_DRAW);

        u32 index = 0;
        u32 offset = 0;
        for (auto attr: layout.attributes) {
            if (attr.type != ShaderUniformType::Int) {
                glVertexAttribPointer(index, ShaderDataType::Size(attr.type) / sizeof(float), GL_FLOAT, 0, layout.stride,
                                      reinterpret_cast<void *>(offset));
            } else {
                glVertexAttribPointer(index, ShaderDataType::Size(attr.type) / sizeof(int32_t), GL_INT, 0, layout.stride,
                                      reinterpret_cast<void *>(offset));
            }
            glEnableVertexAttribArray(index);
            index++;
            offset += attr.offset;
        }
    }

    void OpenGLVertexBuffer::Bind() const {
        assert(m_ID != 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    OpenGLVertexBuffer OpenGLVertexBuffer::Create(const VertexLayout &layout, float *data, u32 length) {
        return OpenGLVertexBuffer{layout, data, length};
    }

    OpenGLVertexBuffer OpenGLVertexBuffer::Create(const VertexLayout &layout, Vertex *data, u32 length) {
        return OpenGLVertexBuffer{layout, data, length};
    }

}