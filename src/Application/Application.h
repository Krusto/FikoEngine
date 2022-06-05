//
// Created by KSTOYAN2 on 6/3/2022.
//
#pragma once

#include "../FikoEngine.h"
#include "../Core/Window.h"

#include <string>
#include <filesystem>

namespace FikoEngine{
struct ApplicationSpec{
  std::string ApplicationName;
  std::string WorkingDirectory;
  Version AppVersion;
};
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
};
}