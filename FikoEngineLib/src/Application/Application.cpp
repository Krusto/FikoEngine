//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#include "Application.h"
#include <Core/Core.h>
#include <Renderer/RendererAPI.h>
#include <ImGUI/ImGUILayer.h>

FikoEngine::Application* FikoEngine::Application::s_Application;

void FikoEngine::Application::Run() {

    auto imguiLayer = Ref<Layer>(new ImGUILayer(m_ApplicationSpec));

    LayerStack::PushLayer(imguiLayer);

    LayerStack::InitLayers(m_Window);

    float dt = 0,before,after;
    while (!m_Window->ShouldClose()) {
        imguiLayer->Begin();
        for (auto& layer : LayerStack::data()) {
            before = (float)glfwGetTime();
            layer->OnImGuiDraw();
            layer->OnUpdate(dt);

            after = (float)glfwGetTime();
            dt = after - before;
        }
        imguiLayer->End();

        m_Window->Update();
    }

}

void FikoEngine::Application::Init(const FikoEngine::ApplicationSpec &spec) {
    m_ApplicationSpec = spec;
    m_ApplicationSpec.WorkingDirectory = std::filesystem::absolute(spec.WorkingDirectory).string();
    Logger::Create();

    m_Window = Window::Create({m_ApplicationSpec.ApplicationName,1280,720});

    RendererSpec rendererSpec;
    rendererSpec.SurfaceSize = {1280,720};

    Renderer::Init(rendererSpec,m_ApplicationSpec);
}

void FikoEngine::Application::Destroy() {
    m_Window->Close();

    LayerStack::DestroyLayers();
    LayerStack::PopLayers();

    Renderer::Shutdown();

    glfwDestroyWindow(m_Window->GetHandle());
    glfwTerminate();
}
