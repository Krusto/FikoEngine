//
// Created by KSTOYAN2 on 6/3/2022.
//

#include "Application.h"
bool FikoEngine::Application::Run() {

    m_Window = Window::Create({"FIKO_ENGINE",1280,720});
    m_Renderer = new Renderer();
    m_Renderer->Init({m_Window->GetSpec().width,m_Window->GetSpec().height},m_ApplicationSpec);

    while(true){
        m_Window->Begin();
        m_Window->Loop();
        m_Window->End();
    }
    delete m_Window;
    return true;
}

void FikoEngine::Application::Destroy() {

}
