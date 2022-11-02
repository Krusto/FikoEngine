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
    Application(const ApplicationSpec& spec) : m_ApplicationSpec(spec){
        m_ApplicationSpec.WorkingDirectory = std::filesystem::absolute(spec.WorkingDirectory).string();
    }

    auto& Spec(){return m_ApplicationSpec;}

    bool Run();
    void Destroy();
    static bool ReadyToExit;

    static Ref<Renderer> s_Renderer;
private:
    ApplicationSpec m_ApplicationSpec;
    Window* m_Window;
};
}