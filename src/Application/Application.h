//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//
#pragma once

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
private:
    ApplicationSpec m_ApplicationSpec;
    Window* m_Window;
    std::shared_ptr<Renderer> m_Renderer;
};
}