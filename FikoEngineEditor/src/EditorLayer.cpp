#include "EditorLayer.h"

EditorLayer::EditorLayer(const FikoEngine::ApplicationSpec& spec) {
    m_Name = "Editor Layer";
    m_AppSpec = spec;
    m_AppSpec.WorkingDirectory = std::filesystem::absolute(spec.WorkingDirectory).string();
    m_CurrentScene = nullptr;
}

void EditorLayer::Init(WeakRef<FikoEngine::Window> window) {
    m_Window = window;
    m_CurrentScene = FikoEngine::SceneSerializer::Deserialize(m_AppSpec.WorkingDirectory+"/assets/testScene.yaml");

    m_HierarchyPanel = Ref<HierarchyPanel>::Create(window);
    m_InspectorPanel = Ref<InspectorPanel>::Create();
    m_AssetsPanel = Ref<AssetsPanel>::Create(std::filesystem::path(m_AppSpec.WorkingDirectory+"/assets"));

    auto windowPtr = m_Window.Lock();
    if(windowPtr)
        m_Framebuffer = FikoEngine::Framebuffer::Create(windowPtr->GetSpec().width,windowPtr->GetSpec().height);
}

void EditorLayer::OnAttach() {
}

void EditorLayer::OnDetach() {
}
void EditorLayer::Destroy() {
    delete m_CurrentScene;
}

void EditorLayer::OnUpdate(float dt) {
    FikoEngine::Entity primaryCamera;
    for (auto &camera: m_CurrentScene->GetEntitiesWith<FikoEngine::CameraComponent>()) {
        if (camera.GetComponent<FikoEngine::CameraComponent>().primary) {
            primaryCamera = camera;
            std::string Tag = primaryCamera.GetComponent<FikoEngine::TagComponent>().Tag;
        }
    }

    if (primaryCamera.IsValid()) {
        auto entityCameraTransform = primaryCamera.GetComponent<FikoEngine::TransformComponent>();
        auto camera = primaryCamera.GetComponent<FikoEngine::CameraComponent>().camera;
        camera->SetPosition(entityCameraTransform.position);
        camera->SetRotation(entityCameraTransform.rotation);
        camera->Update();

        FikoEngine::Renderer::BeginFrame();

        m_Framebuffer->Bind();
        FikoEngine::Renderer::ClearColor(glm::vec4{0.0, 0.0, 0.0, 1.0});

        for (auto &drawable: m_CurrentScene->GetEntitiesWith<FikoEngine::MeshComponent>()) {
            FikoEngine::Renderer::SubmitEntity(drawable, primaryCamera.GetComponent<FikoEngine::CameraComponent>().camera);
        }

        FikoEngine::Renderer::Flush();

        FikoEngine::Renderer::EndFrame();

        m_Framebuffer->Unbind();
    }

}

void EditorLayer::OnWindowResizeEvent(int width, int height) {

}

void EditorLayer::OnImGuiDraw() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene")){
                auto path = FileDialogs::NewFile("");
                if(!path.empty()){
                    FikoEngine::SceneSerializer::Serialize(m_CurrentScene->GetHandle().GetComponent<FikoEngine::FileComponent>().Path+"/"+
                                               m_CurrentScene->GetHandle().GetComponent<FikoEngine::TagComponent>().Tag+".yaml",m_CurrentScene);
                    delete m_CurrentScene;
                    m_CurrentScene = new FikoEngine::Scene(std::filesystem::path(path).filename().stem().string(),std::filesystem::path(path).parent_path().string());
                }
            }
            if (ImGui::MenuItem("Open Folder")) {
                auto windowPtr = m_Window.Lock();
                if (windowPtr) {
                    auto path = FileDialogs::OpenFolder(windowPtr->GetHandle());
                    if (!path.empty())
                        m_AssetsPanel->LoadDirectory(path);
                }
            }
            if (ImGui::MenuItem("Open Scene")) {
                auto windowPtr = m_Window.Lock();
                if (windowPtr) {
                    auto path = FileDialogs::OpenFile(windowPtr->GetHandle(), "").string();
                    if (!path.empty()) {
                        FikoEngine::Scene *newScene = FikoEngine::SceneSerializer::Deserialize(path);
                        if (newScene) {
                            delete m_CurrentScene;
                            m_CurrentScene = newScene;
                        }
                    }
                }
            }
            if (ImGui::MenuItem("Save")){
                FikoEngine::SceneSerializer::Serialize(m_CurrentScene->GetHandle().GetComponent<FikoEngine::FileComponent>().Path+"/"+
                                           m_CurrentScene->GetHandle().GetComponent<FikoEngine::TagComponent>().Tag+".yaml",m_CurrentScene);
            }
            if (ImGui::MenuItem("Save As")){
                FikoEngine::SceneSerializer::Serialize(FileDialogs::SaveFile(""),m_CurrentScene);
            }
            if (ImGui::MenuItem("Exit")) { SetShouldExit(true); }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    m_HierarchyPanel->OnImGUIRender(m_CurrentScene);
    m_AssetsPanel->OnImGUIRender(&m_CurrentScene);
    ImGui::Begin("Console");
    {
        ImGui::End();
    }

    m_InspectorPanel->OnImGUIRender(m_CurrentScene,m_Window);

    ImGui::Begin("Viewport");
    {
        ImVec2 size = ImGui::GetContentRegionAvail();
        if (m_ViewportSize.width != (uint32_t)size.x || m_ViewportSize.height != (uint32_t)size.y) {
            m_Framebuffer->Resize((uint32_t) size.x, (uint32_t) size.y);
            if (m_CurrentScene->FindEntity("EditorCamera").HasComponent<FikoEngine::CameraComponent>()) {
                m_CurrentScene->FindEntity("EditorCamera").GetComponent<FikoEngine::CameraComponent>().camera->ChangeViewport(
                        (uint32_t) size.x, (uint32_t) size.y);
            }
        }
        ImGui::Image((void *) m_Framebuffer->GetColorAttachmentID(), size);

        ImGui::End();
    }
}

void EditorLayer::Begin() {

}

void EditorLayer::End() {

}

void EditorLayer::OnWindowShouldCloseEvent() {
    auto windowPtr = m_Window.Lock();
    if(windowPtr)
        windowPtr->Close();
}
