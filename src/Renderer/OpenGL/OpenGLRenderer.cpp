#include "OpenGLRenderer.h"

namespace FikoEngine {
    void OpenGLRenderer::ClearColor(glm::vec4 color) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::DrawIndexed(Ref<VertexArray> &va) {
        va->Bind();
        glDrawElements(GL_TRIANGLES, va->IndexCount, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::DrawQuad2D(glm::vec2 position, glm::vec2 size, glm::vec3 color) {
    }

    void OpenGLRenderer::InitImGUI() {

    }
}