#include "EditorLayer.h"
#include "Core/Platform/Windows/WindowsPlatformUtils.h"
#include "AssetsPanel.hpp"
#include <Renderer/Viewport.h>
#include <imgui.h>
#include <Scene/Entity.h>
#include <Core/Ref.h>
#include <iostream>
#include <glm/vec4.hpp>

namespace FikoEngine {
    EditorLayer::EditorLayer(ApplicationSpec spec) {
        m_Name = "Editor";
        m_AppSpec = spec;
    }

    void EditorLayer::Init(Ref<Window> window) {
        m_Window = window;
        m_CurrentScene = new Scene();
        m_HierarchyPanel = HierarchyPanel(m_CurrentScene,window);
        m_InspectorPanel = InspectorPanel(m_CurrentScene);
        m_AssetsPanel = AssetsPanel(window,m_CurrentScene, std::filesystem::path(m_AppSpec.WorkingDirectory+"/assets"));
        m_Framebuffer = Framebuffer::Create(window->GetSpec().width,window->GetSpec().height);
        m_Framebuffer->Bind();

<<<<<<< HEAD
        std::vector<std::string> shader_materials = {"BlinnPhongTextured","BlinnPhongDiffuseTextured","BlinnPhongFlat","Light"};
=======
        m_CurrentScene->AddShader("FlatShader", Shader::Load("./assets/flat2D"));
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650

        for(auto& name : shader_materials){
            m_CurrentScene->AddShader(name,Shader::Load(m_AppSpec.WorkingDirectory+"/assets/Shaders/"+name));
            m_CurrentScene->AddMaterial(Material::Create(m_CurrentScene->GetShader(name), name));
        }

        auto BlinnPhongTexturedMaterial = m_CurrentScene->GetMaterial("BlinnPhongTextured");
        auto BlinnPhongDiffuseTexturedMaterial = m_CurrentScene->GetMaterial("BlinnPhongDiffuseTextured");
        auto BlinnPhongFlatMaterial = m_CurrentScene->GetMaterial("BlinnPhongFlat");

        BlinnPhongTexturedMaterial->GetShader()->AddResource("Diffuse", ShaderResourceDeclaration{"Diffuse", 0, 1});
        BlinnPhongTexturedMaterial->GetShader()->AddResource("Specular", ShaderResourceDeclaration{"Specular", 1, 1});

        BlinnPhongDiffuseTexturedMaterial->GetShader()->AddResource("Diffuse", ShaderResourceDeclaration{"Diffuse", 0, 1});

        BlinnPhongTexturedMaterial->Set("material.shininess", 40.0f);
        BlinnPhongTexturedMaterial->Set("material.ambient", glm::vec3(0.1,0.1,0.1));

        BlinnPhongFlatMaterial->Set("material.shininess", 40.0f);
        BlinnPhongFlatMaterial->Set("material.ambient", glm::vec3(0.1,0.1,0.1));
        BlinnPhongFlatMaterial->Set("material.diffuse", glm::vec3(0.75,0.6,0.22));
        BlinnPhongFlatMaterial->Set("material.specular", glm::vec3(0.62,0.55,0.36));

        BlinnPhongDiffuseTexturedMaterial->Set("material.ambient", glm::vec3(0.1,0.1,0.1));
        BlinnPhongDiffuseTexturedMaterial->Set("material.specular", glm::vec3(0.62,0.55,0.36));
        BlinnPhongDiffuseTexturedMaterial->Set("material.shininess", 40.0f);

        m_CurrentScene->AddEntity("EditorCamera")
                .AddComponent<CameraComponent>()
                .AddComponent<TransformComponent>()
                .GetComponent<CameraComponent>().camera = Ref<Camera>::Create(CameraSpec(m_Framebuffer->GetViewportSize(), 90.0));

        m_CurrentScene->FindEntity("EditorCamera").GetComponent<TransformComponent>().position = { 0,0,3 };
        m_CurrentScene->FindEntity("EditorCamera").GetComponent<TransformComponent>().size = { 0.2,0.2,0.2};
        m_CurrentScene->FindEntity("EditorCamera").GetComponent<CameraComponent>().primary = true;

<<<<<<< HEAD
        auto light = m_CurrentScene->AddEntity("Light Source")
                .AddComponent<TransformComponent>()
                .AddComponent<MeshComponent>()
                .AddComponent<MaterialComponent>()
                .AddComponent<LightComponent>();

        light.GetComponent<TransformComponent>().position = glm::vec3(1.2,2.0,2.0);
        light.GetComponent<TransformComponent>().size = glm::vec3(0.05,0.05,0.05);
        light.GetComponent<MeshComponent>() = MeshComponent::Generate(light, MeshType::Cube);

        light.GetComponent<LightComponent>().intensity = 1;
        light.GetComponent<LightComponent>().ambientColor = glm::vec3(0.1,0.1,0.1);
        light.GetComponent<LightComponent>().diffuseColor = glm::vec3(0.5,0.5,0.5);
        light.GetComponent<LightComponent>().specularColor = glm::vec3(1,1,1);

        light.GetComponent<MaterialComponent>().isLightDependent = false;
        light.GetComponent<MaterialComponent>().material = m_CurrentScene->GetMaterial("Light");

        auto entity = m_CurrentScene->AddEntity("Cube")
                .AddComponent<TransformComponent>()
                .AddComponent<MaterialComponent>()
                .AddComponent<MeshComponent>();

        entity.GetComponent<MaterialComponent>().isLightDependent = true;
        entity.GetComponent<MaterialComponent>().material = m_CurrentScene->GetMaterial("BlinnPhongFlat");
        entity.GetComponent<MeshComponent>() = MeshComponent::Generate(entity, MeshType::Cube);
=======
        auto testObject = m_CurrentScene->AddEntity("Test Object");
        testObject.AddComponent<MeshComponent>();
        testObject.AddComponent<MaterialComponent>();
        testObject.AddComponent<TransformComponent>();

        testObject.GetComponent<MeshComponent>() = MeshComponent::Generate(testObject, MeshType::Quad);
        testObject.GetComponent<MaterialComponent>().material = m_CurrentScene->GetMaterial("example_material");

>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
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

            Renderer::BeginFrame();

            m_Framebuffer->Bind();
            Renderer::ClearColor(glm::vec4{0.0, 0.0, 0.0, 1.0});

            for (auto &drawable: m_CurrentScene->GetEntitiesWith<MeshComponent>()) {
                Entity entity = {drawable, m_CurrentScene};
<<<<<<< HEAD
                //entity.GetComponent<MaterialComponent>().material->GetShader()->Bind();
                //Renderer::DrawIndexed(entity.GetComponent<MeshComponent>().GetVA());
                Renderer::SubmitEntity(entity, primaryCamera.GetComponent<CameraComponent>().camera);
=======
                Renderer::DrawEntity(entity);
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
            }

            Renderer::Flush();

            Renderer::EndFrame();

            m_Framebuffer->Unbind();
        }

    }

    void EditorLayer::OnWindowResizeEvent(int width, int height) {

    }

    void EditorLayer::OnImGuiDraw() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open Folder")) {
                    m_AssetsPanel.LoadDirectory(FileDialogs::OpenFolder(m_Window->GetHandle()));
                }
                if (ImGui::MenuItem("Exit")) { SetShouldExit(true); }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_HierarchyPanel.OnImGUIRender();
        m_AssetsPanel.OnImGUIRender();
        ImGui::Begin("Console");
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