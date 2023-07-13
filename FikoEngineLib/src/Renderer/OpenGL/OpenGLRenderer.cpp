#include "OpenGLRenderer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    void OpenGLRenderer::InitImGUI(WeakRef<Window> window) {
        static std::string glsl_version = "#version 150";

        auto windowPtr = window.Lock();
        if(windowPtr) {
            ImGui_ImplGlfw_InitForOpenGL(windowPtr->GetHandle(), true);
            ImGui_ImplOpenGL3_Init(glsl_version.c_str());
        }
    }

    void OpenGLRenderer::Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) {

    }
}