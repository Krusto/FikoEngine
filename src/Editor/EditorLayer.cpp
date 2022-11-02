#include "EditorLayer.h"
#include <Renderer/Viewport.h>
#include <imgui.h>
#include <Scene/Entity.h>
#include <Core/Ref.h>
#include <iostream>
#include <glm/vec4.hpp>

namespace FikoEngine {
    EditorLayer::EditorLayer() {
        m_Name = "Editor";

    }

    void EditorLayer::Init(Window *window) {
        this->window = window;
        m_CurrentScene = new Scene();
        m_HierarchyPanel = HierarchyPanel(m_CurrentScene);
        m_InspectorPanel = InspectorPanel(m_CurrentScene);
        m_Framebuffer = Framebuffer::Create(window->GetSpec().width,window->GetSpec().height);
        m_Framebuffer->Bind();

        m_CurrentScene->AddShader("FlatShader", Shader::Load("./assets/basic"));

        m_CurrentScene->AddMaterial(Material::Create(m_CurrentScene->GetShader("FlatShader"), "example_material"));



        //m_CurrentScene->AddMaterial(Material::Create(m_CurrentScene->GetShader("FlatShader"), "TestObjectMaterial"));

        Renderer::AddMaterial(m_CurrentScene->GetMaterial("example_material"));
        /*m_CurrentScene->GetMaterial("example_material")
                ->Set("u_DiffuseColor", glm::vec4(1, 1, 1, 1));*/


        m_CurrentScene->AddEntity("EditorCamera")
                .AddComponent<CameraComponent>()
                .AddComponent<TransformComponent>()
                .GetComponent<CameraComponent>().camera = Ref<Camera>::Create(
                CameraSpec(m_Framebuffer->GetViewportSize(), 90.0));

        m_CurrentScene->FindEntity("EditorCamera").GetComponent<CameraComponent>().primary = true;

       /* auto testObject = m_CurrentScene->AddEntity("Test Object");
        testObject.AddComponent<MeshComponent>();
        testObject.AddComponent<MaterialComponent>();
        testObject.AddComponent<TransformComponent>();

        testObject.GetComponent<MeshComponent>() = MeshComponent::Generate(testObject, MeshType::Quad);
        testObject.GetComponent<MaterialComponent>().material = m_CurrentScene->GetMaterial("TestObjectMaterial");
*/
    }

    void EditorLayer::OnAttach() {
    }

    void EditorLayer::OnDetach() {
    }

    void EditorLayer::OnUpdate(float dt) {
        Entity primaryCamera;
        for (auto &camera: m_CurrentScene->GetEntitiesWith<CameraComponent>()) {
            if ((Entity{camera, m_CurrentScene}).GetComponent<CameraComponent>().primary) {
                primaryCamera = Entity{camera, m_CurrentScene};
                std::string Tag = primaryCamera.GetComponent<TagComponent>().Tag;
            }
        }

        if (primaryCamera.IsValid()) {
            auto &entityCameraTransform = primaryCamera.GetComponent<TransformComponent>();
            auto &camera = primaryCamera.GetComponent<CameraComponent>().camera;
            camera->SetPosition(entityCameraTransform.position);
            camera->SetRotation(entityCameraTransform.rotation);
            camera->Update();

            m_Framebuffer->Bind();
            Renderer::ClearColor(glm::vec4{0.0, 0.0, 0.0, 1.0});

            for (auto &drawable: m_CurrentScene->GetEntitiesWith<MeshComponent>()) {
                Entity entity = {drawable, m_CurrentScene};
                Renderer::SubmitEntity(entity, primaryCamera.GetComponent<CameraComponent>().camera);
            }

            Renderer::Flush();

            m_Framebuffer->Unbind();
        }

    }

    void EditorLayer::OnWindowResizeEvent(int width, int height) {
    }

    void EditorLayer::OnImGuiDraw() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) { SetShouldExit(true); }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_HierarchyPanel.OnImGUIRender();

        ImGui::Begin("Console");
        {
            ImGui::End();
        }
        ImGui::Begin("Assets");
        {
            ImGui::End();
        }
        m_InspectorPanel.OnImGUIRender(m_CurrentScene->GetSelectedEntity());

        ImGui::Begin("Viewport");
        {
            ImVec2 size = ImGui::GetContentRegionAvail();
            ViewportSize vSize = ViewportSize{(uint32_t) size.x, (uint32_t) size.y};
            if (m_ViewportSize != vSize) { // intellisense bug
                m_Framebuffer->Resize((uint32_t) size.x, (uint32_t) size.y);
                if (m_CurrentScene->FindEntity("EditorCamera").HasComponent<CameraComponent>()) {
                    m_CurrentScene->FindEntity("EditorCamera").GetComponent<CameraComponent>().camera->ChangeViewport(
                            (uint32_t) size.x, (uint32_t) size.y);
                }
            }
            ImGui::Image((void *) m_Framebuffer->GetColorAttachmentID(), size);

            ImGui::End();
        }
    }

}