#pragma once
#include <Layer/Layer.h>
#include <Renderer/Window.h>
#include <memory>

namespace FikoEngine {
    class ImGUILayer : public FikoEngine::Layer {
    public:
        ImGUILayer() = default;

        explicit ImGUILayer(const FikoEngine::ApplicationSpec& spec);

        void Init(WeakRef<Window> window) override;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float dt) override;

        void OnImGuiDraw() override;

        void Begin() override;

        void End() override;

        void Destroy() override {};

        void OnMouseMoveEvent(int width, int height) override {};

        void OnKeyboardEvent(int action, int key) override {};

        void OnWindowResizeEvent(int width, int height) override {};

        void OnWindowShouldCloseEvent() override;

    protected:
        WeakRef<Window> m_Window;
        ApplicationSpec m_ApplicationSpec;
    };
}
namespace ImGui {
    static inline int currentID = 0;

    [[maybe_unused]]static int NextID() {
        ImGui::currentID++;
        return ImGui::currentID;
    }
}