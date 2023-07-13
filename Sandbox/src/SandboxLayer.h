#pragma once
#include <FikoEngine.h>

class SandboxLayer : public FikoEngine::Layer {
public:
    explicit SandboxLayer(const FikoEngine::ApplicationSpec& spec);
    ~SandboxLayer() override{
        m_Framebuffer->Destroy();
        m_Framebuffer.Reset();
    }

    void Init(WeakRef<FikoEngine::Window> window) override;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float dt) override;

    void Destroy() override;

    void OnImGuiDraw() override;

    void OnMouseMoveEvent(int width, int height) override {};

    void OnKeyboardEvent(int action, int key) override {};

    void OnWindowResizeEvent(int width, int height) override;

    void OnWindowShouldCloseEvent() override {
        SetShouldExit(true);
    };

    void Begin() override {}
    void End() override {}
protected:
    WeakRef<FikoEngine::Window> m_Window;

    FikoEngine::Scene* m_CurrentScene;

    Ref<FikoEngine::Framebuffer> m_Framebuffer;

    ViewportSize m_ViewportSize;

    FikoEngine::ApplicationSpec m_AppSpec;

};
