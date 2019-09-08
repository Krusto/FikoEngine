#include "Application.h"
#include "Renderer/Renderer.h"
#include "Logger/Logger.h"
#include <GLFW/glfw3.h>

namespace FikoEngine {
    void Application::CreateWindow(const char *Title, int width, int height) {
        m_Window.Create(width, height, Title, WindowMode::Windowed);
    }

    Window Application::GetWindow() {
        return m_Window;
    }

    bool Application::Run() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);
        while (!GetWindow().ShouldClose()) {
            if (GetWindow().GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                GetWindow().SetWindowShouldClose(GLFW_TRUE);
            }
            Loop();
            return true;
        }
        return true;
    }

    Application::Application() {
        glfwInit();
        m_Window.Create();

        Log::Init();

        Renderer::Init(m_Window);
    }

    Application::~Application() {
        m_Window.Destroy();
        glfwTerminate();
    }

    void Application::Loop() {
        glfwPollEvents();

    }
}