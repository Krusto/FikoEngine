//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include <Core/Core.h>
#include <glm/glm.hpp>
#include "Window.h"
#include "RendererSpec.h"
#include "Viewport.h"
#include "Renderer.h"

namespace FikoEngine {

class VertexArray;
class RendererAPI {
public:
    ~RendererAPI() {};

    enum API{
        None,
        OpenGL,
        Vulkan
    };

    static RendererAPI::API Current(){return RendererAPI::s_api;}
    static void SetApi(API api) { RendererAPI::s_api = api; }

    inline static API s_api = API::OpenGL;

public:
    virtual void Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) = 0;
    virtual void InitImGUI(WeakRef<Window> window) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void RenderQuad() = 0;
    virtual void RenderMesh() = 0;
    virtual void RenderMeshWithMaterial() = 0;
    virtual void ClearColor(glm::vec4 color) = 0;
    virtual void DrawIndexed(Ref<VertexArray>& va) = 0;
    virtual void DrawQuad2D(glm::vec2 position, glm::vec2 size, glm::vec3 color) = 0;

};
}