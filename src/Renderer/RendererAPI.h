//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#pragma once

#include <glm/vec4.hpp>
#include "../Core/Core.h"
#include "Window.h"
#include "RendererSpec.h"
#include "Viewport.h"
#include "Renderer.h"
#include "Material.h"

namespace FikoEngine {

///Class interfacing the renderer with the api
class RendererAPI {
public:
    enum API{
        None,
        OpenGL,
        Vulkan
    };

    static RendererAPI::API Current(){return RendererAPI::s_api;}
    inline static API s_api = API::Vulkan;

public:

    static void Init(FikoEngine::RendererSpec rendererSpec, ApplicationSpec applicationSpec);
    static void InitImGUI();
    static void Destroy();

    static void ResizeFramebuffer(ViewportSize size);
    static void ClearColor(glm::vec4 color = {0.0f,0.0f,0.0f,1.0f});
    static void SetActiveWindow(Window* window);
    static void AddMaterial(Ref<Material> material);

    static void Draw();

private:
    inline static std::unordered_map<std::string_view,Ref<Material>> s_Materials;
};
}