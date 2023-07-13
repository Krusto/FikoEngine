#include "SandboxLayer.h"

SandboxLayer::SandboxLayer(const FikoEngine::ApplicationSpec& spec) {
    m_Name = "Sandbox Layer";
    m_AppSpec = spec;
    m_AppSpec.WorkingDirectory = std::filesystem::absolute(spec.WorkingDirectory).string();
    m_CurrentScene = nullptr;
}

void SandboxLayer::Init(WeakRef<FikoEngine::Window> window) {
    m_Window = window;
    m_CurrentScene = FikoEngine::SceneSerializer::Deserialize(m_AppSpec.WorkingDirectory+"/assets/testScene.yaml");

    auto windowPtr = m_Window.Lock();
    m_Framebuffer = FikoEngine::Framebuffer::Create(windowPtr->GetSpec().width,windowPtr->GetSpec().height);
}

void SandboxLayer::OnAttach() {
}

void SandboxLayer::OnDetach() {
}
void SandboxLayer::Destroy() {
    if(m_CurrentScene)
        delete m_CurrentScene;
}

void SandboxLayer::OnUpdate(float dt) {
    FikoEngine::Entity primaryCamera;
    for (auto &camera: m_CurrentScene->GetEntitiesWith<FikoEngine::CameraComponent>()) {
        if (camera.GetComponent<FikoEngine::CameraComponent>().primary) {
            primaryCamera = camera;
        }
    }

    if (primaryCamera.IsValid()) {
        auto entityCameraTransform = primaryCamera.GetComponent<FikoEngine::TransformComponent>();
        auto camera = primaryCamera.GetComponent<FikoEngine::CameraComponent>().camera;
        camera->SetPosition(entityCameraTransform.position);
        camera->SetRotation(entityCameraTransform.rotation);
        camera->Update();

        FikoEngine::Renderer::BeginFrame();

        auto framebufferPtr = m_Framebuffer;
        if(framebufferPtr) {

            framebufferPtr->Bind();
            FikoEngine::Renderer::ClearColor(glm::vec4{0.0, 0.0, 0.0, 1.0});

            for (auto &drawable: m_CurrentScene->GetEntitiesWith<FikoEngine::MeshComponent>()) {
                FikoEngine::Renderer::SubmitEntity(drawable,
                                                   primaryCamera.GetComponent<FikoEngine::CameraComponent>().camera);
            }

            FikoEngine::Renderer::Flush();

            framebufferPtr->Unbind();
        }
        FikoEngine::Renderer::EndFrame();

    }

}

void SandboxLayer::OnWindowResizeEvent(int width, int height) {

}

void SandboxLayer::OnImGuiDraw() {
    ImGui::Begin("Viewport");
    {

        auto framebufferPtr = m_Framebuffer;
        if(framebufferPtr) {

            ImVec2 size = ImGui::GetContentRegionAvail();
            if (m_ViewportSize.width != (uint32_t) size.x || m_ViewportSize.height != (uint32_t) size.y) {
                framebufferPtr->Resize((uint32_t) size.x, (uint32_t) size.y);
                FikoEngine::Entity primaryCamera;
                for (auto &camera: m_CurrentScene->GetEntitiesWith<FikoEngine::CameraComponent>()) {
                    if (camera.GetComponent<FikoEngine::CameraComponent>().primary) {
                        primaryCamera = camera;
                    }
                }
                if (primaryCamera.IsValid()) {
                    primaryCamera.GetComponent<FikoEngine::CameraComponent>().camera->ChangeViewport(
                            (uint32_t) size.x, (uint32_t) size.y);
                }
            }
            ImGui::Image((void *) framebufferPtr->GetColorAttachmentID(), size);
        }
        ImGui::End();
    }
}
