//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#include "Application.h"
#include <Core/Ref.h>
#include <Renderer/RendererAPI.h>
#include "Editor/EditorLayer.h"
#include "ImGUI/ImGUILayer.h"

FikoEngine::Application FikoEngine::Application::s_Application;

bool FikoEngine::Application::Run() {
    Logger::Init();

    m_Window = Window::Create({m_ApplicationSpec.ApplicationName,1280,720});

    RendererSpec rendererSpec;
    rendererSpec.SurfaceSize = {1280,720};

    Renderer::Init(rendererSpec,m_ApplicationSpec);

    auto imguiLayer = Ref<ImGUILayer>::Create(m_ApplicationSpec);
    auto editorLayer = Ref<EditorLayer>::Create(m_ApplicationSpec);
    LayerStack::PushLayer(editorLayer);
    LayerStack::PushLayer(imguiLayer);

    for (auto layer : LayerStack::data()) {
        layer.second->Init(m_Window);
    }

    float dt = 0,before = 0,after = 0;
    while (!m_Window->ShouldClose()) {
        imguiLayer->Begin();
        for (auto& [layerName, layer] : LayerStack::data()) {
            before = (float)glfwGetTime();
            layer->OnImGuiDraw();
            layer->OnUpdate(dt);
            if (layer->ShouldExit()) {
                glfwSetWindowShouldClose(m_Window->GetHandle(), GLFW_TRUE);
                break;
            }
            after = (float)glfwGetTime();
            dt = after - before;
        }
        imguiLayer->End();

        m_Window->Update();
    }

    m_Window->Close();

    for (auto& layer : LayerStack::data()) {
        layer.second->Destroy();
    }

    LayerStack::PopLayer("Editor Layer");
    LayerStack::PopLayer("ImGui Layer");

    Renderer::Shutdown();

    glfwDestroyWindow(m_Window->GetHandle());
    glfwTerminate();

    m_Window.Reset();

    return true;
}

void FikoEngine::Application::Init(const FikoEngine::ApplicationSpec &spec) {
    m_ApplicationSpec = spec;
    m_ApplicationSpec.WorkingDirectory = std::filesystem::absolute(spec.WorkingDirectory).string();
}

void FikoEngine::Application::Destroy() {
    Renderer::Shutdown();
}
