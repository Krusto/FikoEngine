#pragma once
#include <Layer/Layer.h>
#include <Renderer/Window.h>
#include <memory>

namespace FikoEngine {
    class ImGUILayer : public FikoEngine::Layer {
    public:
        ImGUILayer(ApplicationSpec) { m_Name = "ImGui Layer"; }

        void Init(Ref<Window> window) override;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float dt) override;

        void OnImGuiDraw() override;

        void Begin();

        void End();

        void Destroy() override {};

        void OnMouseMoveEvent(int width, int height) override {};

        void OnKeyboardEvent(int action, int key) override {};

        void OnWindowResizeEvent(int width, int height) override {};

        void OnWindowShouldCloseEvent() override { SetShouldExit(true); };
    protected:
        GLFWwindow *window = nullptr;
    };
}
namespace ImGui {
    static inline int currentID = 0;

    static int NextID() {
        ImGui::currentID++;
        return ImGui::currentID;
    }
}