//
// Created by KSTOYAN2 on 6/3/2022.
//
#pragma once

#include "../FikoEngine.h"
#include "../Core/Window.h"
#include "ApplicationSpec.h"

#include <string>
#include <filesystem>

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
private:
    ApplicationSpec m_ApplicationSpec;
    Window* m_Window;
    Renderer* m_Renderer;
};
}