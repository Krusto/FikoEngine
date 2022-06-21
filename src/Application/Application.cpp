//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#include "Application.h"
void OnWindowClose(GLFWwindow* window){
    FikoEngine::Application::ReadyToExit = true;
}
bool FikoEngine::Application::ReadyToExit{};

bool FikoEngine::Application::Run() {
    Logger::Init();

    m_Window = Window::Create({"FIKO_ENGINE",1280,720});
    m_Window->OnWindowClose(OnWindowClose);
    m_Renderer = std::make_shared<Renderer>();
    m_ApplicationSpec.window = m_Window;
    m_Renderer->Init({m_Window->GetSpec().width,m_Window->GetSpec().height},m_ApplicationSpec);

    while(!Application::ReadyToExit){
       m_Window->Begin();
       m_Window->Loop();

       m_Renderer->Draw();

       m_Window->End();
   }
    m_Renderer->Destroy();
    delete m_Window;
    return true;
}

void FikoEngine::Application::Destroy() {

}
