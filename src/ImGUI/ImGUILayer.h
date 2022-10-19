#pragma once
#include <Layer/Layer.h>
#include <Renderer/Window.h>
#include <memory>

class ImGUILayer : public FikoEngine::Layer {
public:
    ImGUILayer() { m_Name = "IMGUI LAYER"; }
    void Init(FikoEngine::Window* window) override;
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
    FikoEngine::Window* window = nullptr;
};
namespace ImGui {
    static inline int currentID = 0;
    static int NextID() { ImGui::currentID++; return ImGui::currentID; }
}