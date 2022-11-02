//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Renderer.h"
#include "RendererAPI.h"

#include <Renderer/Camera.h>
#include <Renderer/Framebuffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Material.h>
#include <Renderer/MeshBuilder.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Renderer/TextureAtlas.h>
#include <Renderer/Vertex.h>
#include <Renderer/VertexArray.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexLayout.h>
#include <Renderer/Light.h>
#include <Renderer/Viewport.h>
#include <Scene/Entity.h>
namespace FikoEngine {
    void Renderer::Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec) {
        Renderer::s_RendererSpec = rendererSpec;
        RendererAPI::Init(rendererSpec, applicationSpec);
    }
    void Renderer::Draw(){
        RendererAPI::Draw();
    }
    void Renderer::Destroy(){
        RendererAPI::Destroy();
    }
    void Renderer::ResizeFramebuffer(ViewportSize size){
        RendererAPI::ResizeFramebuffer(size);
    }

    void Renderer::ClearColor(glm::vec4 color) {
        RendererAPI::ClearColor(color);
    }

    void Renderer::SubmitEntity(Entity entity, Ref<Camera> camera) {
        //TODO
        Ref<Material> material = entity.GetComponent<MaterialComponent>().material;


    }

    void Renderer::AddMaterial(Ref<Material> material){
        RendererAPI::AddMaterial(material);
    }

    void Renderer::Flush() {
        //TODO
    }

    void Renderer::InitImGUI() {
        RendererAPI::InitImGUI();
    }

    void Renderer::SetActiveWindow(Window* window) {
        RendererAPI:SetActiveWindow(window);
    }

}