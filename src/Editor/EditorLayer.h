#pragma once
#include <Layer/Layer.h>
#include <Renderer/Renderer.h>
#include <Editor/HierarchyPanel.h>
#include <Editor/InspectorPanel.h>
#include <Scene/Scene.h>
#include <Renderer/Shader.h>
#include <Renderer/Framebuffer.h>
#include <Editor/AssetsPanel.hpp>

namespace FikoEngine {
    class Window;

    class EditorLayer : public Layer {
    public:
        EditorLayer(ApplicationSpec spec);

        void Init(Ref<Window> window) override;

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
        };
    protected:
        Ref<Window> m_Window;
        ViewportSize windowSize;

        Scene *m_CurrentScene;

        Ref<Framebuffer> m_Framebuffer;
        Ref<Shader> m_Shader;
        Ref<Material> m_ExampleMaterial;

        ViewportSize m_ViewportSize;

        HierarchyPanel m_HierarchyPanel;
        InspectorPanel m_InspectorPanel;
        AssetsPanel m_AssetsPanel;

        ApplicationSpec m_AppSpec;

        Entity m_SelectedEntity;
    };
}