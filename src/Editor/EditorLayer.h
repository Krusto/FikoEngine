#pragma once
#include <Layer/Layer.h>
#include <Renderer/Renderer.h>
#include <Editor/HierarchyPanel.h>
#include <Editor/InspectorPanel.h>
#include <Scene/Scene.h>
#include <Renderer/Shader.h>

namespace FikoEngine {
    class Window;

    class EditorLayer : public Layer {
    public:
        EditorLayer();

        void Init(Window *window) override;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float dt) override;

        void Destroy() override {};

        void OnImGuiDraw() override;

        void OnMouseMoveEvent(int width, int height) override {};

        void OnKeyboardEvent(int action, int key) override {};

        void OnWindowResizeEvent(int width, int height) override;

        void OnWindowShouldCloseEvent() override {
            SetShouldExit(true);
            window->Close();
        };
    protected:
        Window *window = nullptr;
        ViewportSize windowSize;

        Scene *m_CurrentScene;

        Ref<Framebuffer> m_Framebuffer;
        Ref<Shader> m_Shader;
        Ref<Material> m_ExampleMaterial;

        ViewportSize m_ViewportSize;

        HierarchyPanel m_HierarchyPanel;
        InspectorPanel m_InspectorPanel;

        Entity m_SelectedEntity;
    };
}