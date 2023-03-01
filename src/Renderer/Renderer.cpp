#include "Renderer.h"
#include "RendererAPI.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <Renderer/OpenGL/OpenGLRenderer.h>
#include <Renderer/OpenGL/OpenGLContext.h>

#include <Renderer/Vulkan/VulkanRenderer.h>

#include <Scene/Entity.h>
#include <iostream>

namespace FikoEngine {
    static RendererAPI *s_RendererAPI = nullptr;

    static RendererAPI *InitRendererAPI() {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::OpenGL :
                return new OpenGLRenderer();
            case RendererAPI::API::Vulkan :
                return new VulkanRenderer();
        }
        return nullptr;
    }

    RendererAPI *Renderer::GetAPI(){
        return s_RendererAPI;
    }

    void Renderer::Init(RendererSpec& rendererSpec, ApplicationSpec applicationSpec) {
        s_RendererAPI = InitRendererAPI();

        s_RendererAPI->Init(rendererSpec,applicationSpec);
    }

    void Renderer::Shutdown(){
        s_RendererAPI->Shutdown();
    }
    void Renderer::InitImGUI() {
        s_RendererAPI->InitImGUI();
    }
    void Renderer::ClearColor(glm::vec4 color) {
        s_RendererAPI->ClearColor(color);
    }

    void Renderer::DrawIndexed(Ref<VertexArray> va) {
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

    void Renderer::DrawMaterialMesh(Mesh mesh, Ref<Material> material) {
        material->GetShader()->Bind();
        material->UpdateForRendering();
        Renderer::DrawMesh(mesh);
    }

    Ref<GraphicsContext> Renderer::CreateGraphicsContext(GLFWwindow *handle) {
        return GraphicsContext::Create(handle);
    }

    void Renderer::SubmitEntity(Entity entity, Ref<Camera> camera) {
        Submit([=]() mutable {
            if (entity.IsValid()) {
                if (entity.HasComponent<MaterialComponent>() && entity.HasComponent<TransformComponent>()) {
                    auto &materialComponent = entity.GetComponent<MaterialComponent>();
                    auto &material = materialComponent.material;
                    if (material)
                        if (material->GetShader()) {
                            const auto Transform = entity.GetComponent<TransformComponent>().GetTransform();

                            material->GetShader()->Bind();
                            material->UpdateForRendering();
                            material->GetShader()->SetUniform("camera.model", Transform);

                            camera->Upload(material->GetShader());

                            if (materialComponent.isLightDependent) {
                                auto lightEntities = entity.m_Scene->GetEntitiesWith<LightComponent>();

                                uint32_t lightIndex = 0;
                                for (auto &lightEntity: lightEntities) {
                                    if (lightIndex == 0) {
                                        auto lightComponent = Entity(
                                                {lightEntity, entity.m_Scene}).GetComponent<LightComponent>();
                                        material->GetShader()->SetUniform("light.ambient", lightComponent.ambientColor);
                                        material->GetShader()->SetUniform("light.diffuse", lightComponent.diffuseColor);
                                        material->GetShader()->SetUniform("light.specular",
                                                                          lightComponent.specularColor);
                                        material->GetShader()->SetUniform("light.position", lightComponent.position);
                                        material->GetShader()->SetUniform("light.intensity", lightComponent.intensity);
                                    }
                                    break;
                                }
                            }

                            if (entity.GetComponent<MeshComponent>().GetVA()) {
                                Renderer::DrawIndexed(entity.GetComponent<MeshComponent>().GetVA());
                            } else if (entity.GetComponent<MeshComponent>().GetVA() && entity.HasComponent<DrawableComponent>()) {
                                Renderer::DrawIndexed(entity.GetComponent<DrawableComponent>().GetVA());
                            }
                        }
                }
            }
        });
    }
}