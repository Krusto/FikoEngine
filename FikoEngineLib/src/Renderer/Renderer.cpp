#include "Renderer.h"
#include "RendererAPI.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <Renderer/OpenGL/OpenGLRenderer.h>
#include <Renderer/OpenGL/OpenGLContext.h>

#include <Renderer/Vulkan/VulkanRenderer.h>

#include <Scene/Entity.h>
#include <Scene/Scene.h>
#include <iostream>

namespace FikoEngine {
    static RendererAPI *s_RendererAPI = nullptr;

    static RendererAPI *CreateRendererAPIInstance() {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL :
                return new OpenGLRenderer();
            case RendererAPI::API::Vulkan :
                return new VulkanRenderer();
            case RendererAPI::None:
                return nullptr;
        }
        return nullptr;
    }

    RendererAPI *Renderer::GetAPIInstance(){
        return s_RendererAPI;
    }

    void Renderer::Init(RendererSpec& rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererAPI = CreateRendererAPIInstance();

        if (s_RendererAPI)
            s_RendererAPI->Init(rendererSpec, applicationSpec);

    }

    void Renderer::InitImGUI(WeakRef<Window> window) {
        if (s_RendererAPI)
            s_RendererAPI->InitImGUI(window);

    }

    void Renderer::Shutdown(){
        if (s_RendererAPI)
            s_RendererAPI->Shutdown();

    }

    void Renderer::ClearColor(glm::vec4 color) {
        if (s_RendererAPI)
            s_RendererAPI->ClearColor(color);

    }
    void Renderer::DrawIndexed(Ref<VertexArray> va) {
        if (s_RendererAPI)
            s_RendererAPI->DrawIndexed(va);

    }

    void Renderer::DrawMesh(Mesh &mesh) {
        auto va = VertexArray::Create((uint32_t) mesh.indices.size());
        va->Bind();
        auto vb = VertexBuffer::Create(Vertex::GetLayout(), (float *) mesh.vertices.data(),
                                       (uint32_t) mesh.vertices.size());
        auto ib = IndexBuffer::Create(mesh.indices.data(), (uint32_t) mesh.indices.size());

        va->AddVertexBuffer(vb);
        va->AddIndexBuffer(ib);

        Renderer::DrawIndexed(va);

    }

    void Renderer::DrawMaterialMesh(Mesh mesh, Material* material) {
        if(material->GetShader().IsValid()) {
            auto shader = material->GetShader().Lock();
            shader->Bind();
            material->UpdateForRendering();
            Renderer::DrawMesh(mesh);
        }
    }

    GraphicsContext* Renderer::CreateGraphicsContext(GLFWwindow *handle) {
        return GraphicsContext::Create(handle);
    }

    void Renderer::SubmitEntity(Entity entity, Ref<Camera> camera) {
        Submit([entity,camera]() mutable {
            if (entity.IsValid()) {
                if (entity.HasComponent<MaterialComponent>() && entity.HasComponent<TransformComponent>()) {
                    auto materialComponent = entity.GetComponent<MaterialComponent>();
                    if (materialComponent.material.IsValid()) {
                        auto material = materialComponent.material.Lock().Raw();
                        if (material && material->GetShader().IsValid()) {
                            const auto Transform = entity.GetComponent<TransformComponent>().GetTransform();

                            auto shader = material->GetShader().Lock().Raw();
                            shader->Bind();
                            material->UpdateForRendering();
                            shader->SetUniform("camera.model", Transform);

                            camera->Upload(shader);

                            if (materialComponent.isLightDependent) {
                                auto lightEntities = entity.m_Scene->GetEntitiesWith<LightComponent>();

                                uint32_t lightIndex = 0;
                                for (auto &lightEntity: lightEntities) {
                                    if (lightIndex == 0) {
                                        auto lightComponent = lightEntity.GetComponent<LightComponent>();
                                        shader->SetUniform("light.ambient",
                                                                          lightComponent.ambientColor);
                                        shader->SetUniform("light.diffuse",
                                                                          lightComponent.diffuseColor);
                                        shader->SetUniform("light.specular",
                                                                          lightComponent.specularColor);
                                        shader->SetUniform("light.position",
                                                                          lightComponent.position);
                                        shader->SetUniform("light.intensity",
                                                                          lightComponent.intensity);
                                    }
                                    break;
                                }
                            }

                            if (entity.GetComponent<MeshComponent>().GetVA()) {
                                Renderer::DrawIndexed(entity.GetComponent<MeshComponent>().GetVA());
                            } else if (entity.GetComponent<MeshComponent>().GetVA() &&
                                       entity.HasComponent<DrawableComponent>()) {
                                Renderer::DrawIndexed(entity.GetComponent<DrawableComponent>().GetVA());
                            }
                        }
                    }
                }
            }
            return;
        });
    }
}