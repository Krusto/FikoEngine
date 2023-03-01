//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//
#pragma once

#include <Core/Ref.h>
#include "../FikoEngine.h"

namespace FikoEngine{

class Application{
public:
    Application() = default;
    Application(const ApplicationSpec& spec) {Init(spec);}

    bool Run();
    void Init(const ApplicationSpec& spec);

    uint32_t GetWidth() { return m_Window->GetSpec().width; }
    uint32_t GetWidth() const { return m_Window->GetSpec().width; }
    uint32_t GetHeight() { return m_Window->GetSpec().height; }
    uint32_t GetHeight() const { return m_Window->GetSpec().height; }

    auto& Spec(){return m_ApplicationSpec;}

    static Application& Get() { return Application::s_Application; }

    Ref<Window> WindowHandle() { return m_Window;}

    void Destroy();
private:
    static Application s_Application;

    Ref<Window> m_Window;
    ApplicationSpec m_ApplicationSpec;
};
}