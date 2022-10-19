#pragma once

#include <string_view>
#include <memory>
#include <Core/Ref.h>
namespace FikoEngine {
    class Window;

    class Layer : public RefCounted {
    public:
        virtual void Init(FikoEngine::Window *window) = 0;

        virtual void OnAttach() = 0;

        virtual void OnUpdate(float dt) = 0;

        virtual void OnDetach() = 0;

        virtual void Destroy() = 0;

        virtual void OnImGuiDraw() = 0;

        virtual void OnMouseMoveEvent(int width, int height) = 0;

        virtual void OnKeyboardEvent(int action, int key) = 0;

        virtual void OnWindowResizeEvent(int width, int height) = 0;

        virtual void OnWindowShouldCloseEvent() = 0;

        std::string_view GetName() { return m_Name; }

        bool ShouldExit() { return shouldExit; }

        void SetShouldExit(bool value) { shouldExit = value; }

    protected:
        bool shouldExit{};
        std::string_view m_Name{};
    };
}