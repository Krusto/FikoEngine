//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include <glm/vec4.hpp>
#include "../Core/Core.h"
#include "Window.h"
#include "Viewport.h"
#include "Camera.h"
#include "Material.h"
#include "VertexArray.h"
#include "Mesh.h"

namespace FikoEngine {

struct RendererSpec {
public:
    ViewportSize SurfaceSize;
    std::vector<const char*> extensions;
};

class Entity;
class RendererAPI;
class Renderer : public RefCounted{
public:
    using FunctionContainer_t = std::vector<std::function<void(void)>>;
    Renderer() = default;
    static void Init(RendererSpec& rendererSpec, ApplicationSpec applicationSpec);
    static void InitImGUI();
<<<<<<< HEAD
    static void Shutdown() {}
    static void BeginFrame() {};
    static void EndFrame() {};
    static void ClearColor(glm::vec4 color);
    static void DrawIndexed(Ref<VertexArray> va);
    static void DrawMesh(Mesh& mesh);
    static void DrawMaterialMesh(Mesh mesh, Ref<Material> material);
    static Ref<GraphicsContext> CreateGraphicsContext(GLFWwindow* handle);
    static RendererAPI* GetAPI();
=======
    static void Draw();
    static void DrawEntity(Entity entity);
    static void Destroy();
    static void ResizeFramebuffer(ViewportSize size);
    static void ClearColor(glm::vec4 color = {0.0f,0.0f,0.0f,1.0f});
    static void SubmitEntity(Entity entity, Ref<Camera> camera);
    static void Flush();
    static void SetActiveWindow(Window* window);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

    static void SubmitEntity(Entity entity, Ref<Camera> camera);

    static void Submit(const std::function<void(void)>& func) {
        s_FunctionContainer.push_back(func);
    }
    template<typename T>
    static void SubmitFlush(T func) {
    }
    static void Flush() {
        for(auto& function : s_FunctionContainer){
            function();
        }
        s_FunctionContainer.clear();
    }
    static inline FunctionContainer_t s_FunctionContainer{};

    inline static RendererSpec s_RendererSpec;
};
}