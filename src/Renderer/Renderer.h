//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include <glm/vec4.hpp>
#include "Window.h"
#include "../Core/Core.h"
#include "Viewport.h"
#include "Camera.h"
#include "Material.h"

namespace FikoEngine {

///Struct which holds renderer specification
struct RendererSpec {
public:
    ViewportSize SurfaceSize;
    std::vector<const char*> extensions;
};
class Entity;
class Renderer : public RefCounted{
public:
    Renderer() = default;
///Function which inits the whole renderer
    static void Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec);
    static void InitImGUI();
    static void Draw();
    static void Destroy();
    static void ResizeFramebuffer(ViewportSize size);
    static void ClearColor(glm::vec4 color = {0.0f,0.0f,0.0f,1.0f});
    static void SubmitEntity(Entity entity, Ref<Camera> camera);
    static void Flush();
    static void SetActiveWindow(Window* window);

    static void AddMaterial(Ref<Material> material);
private:

    inline static RendererSpec s_RendererSpec;
};
}