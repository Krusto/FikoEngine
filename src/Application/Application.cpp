//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#include "Application.h"

std::shared_ptr<FikoEngine::Renderer> FikoEngine::Application::s_Renderer;

void OnWindowClose(GLFWwindow* window){
    FikoEngine::Application::ReadyToExit = true;
}
void OnWindowResize(GLFWwindow* window, i32 width, i32 height){
    FikoEngine::Application::s_Renderer->ResizeFramebuffer({(u32)width,(u32)height});
}
bool FikoEngine::Application::ReadyToExit{};

bool FikoEngine::Application::Run() {
    Logger::Init();

    m_Window = Window::Create({"FIKO_ENGINE",1280,720});
    m_Window->OnWindowClose(OnWindowClose);
    m_Window->OnWindowResize(OnWindowResize);

    s_Renderer = std::make_shared<Renderer>();
    m_ApplicationSpec.window = m_Window;
    s_Renderer->Init({m_Window->GetSpec().width,m_Window->GetSpec().height},m_ApplicationSpec);

    while(!Application::ReadyToExit){
       m_Window->Begin();
       m_Window->Loop();
       s_Renderer->Update();
       s_Renderer->Draw();

       m_Window->End();
    }

    return true;
}

void FikoEngine::Application::Destroy() {
    s_Renderer->Destroy();
    delete m_Window;
}
