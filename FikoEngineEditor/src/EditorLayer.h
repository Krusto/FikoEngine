#pragma once
#include "HierarchyPanel.h"
#include "InspectorPanel.h"
#include "AssetsPanel.hpp"
#include <FikoEngine.h>

class EditorLayer : public FikoEngine::Layer {
public:
    explicit EditorLayer(const FikoEngine::ApplicationSpec& spec);
    ~EditorLayer() override = default;

    void Init(WeakRef<FikoEngine::Window> window) override;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float dt) override;

    void Destroy() override;

    void OnImGuiDraw() override;

    void OnMouseMoveEvent(int width, int height) override {};

    void OnKeyboardEvent(int action, int key) override {};

    void OnWindowResizeEvent(int width, int height) override;

    void OnWindowShouldCloseEvent() override;

    void Begin() override;

    void End() override;

protected:
    WeakRef<FikoEngine::Window> m_Window;

    FikoEngine::Scene* m_CurrentScene;

    Ref<FikoEngine::Framebuffer> m_Framebuffer;

    ViewportSize m_ViewportSize;

    Ref<HierarchyPanel> m_HierarchyPanel;
    Ref<InspectorPanel> m_InspectorPanel;
    Ref<AssetsPanel> m_AssetsPanel;

    FikoEngine::ApplicationSpec m_AppSpec;

};
