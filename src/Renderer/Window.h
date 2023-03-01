//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#pragma once
#include <vulkan/vulkan.h>

#include "../Core/Core.h"
#include "Core/Ref.h"
#include "../Util/Version.h"
#include "Layer/LayerStack.h"

#include "GraphicsContext.h"

#include "Viewport.h"
namespace FikoEngine {
    class Window;

    struct ApplicationSpec {
        std::string ApplicationName;
        std::string WorkingDirectory;
        FikoEngine::Version AppVersion;
    };

///Structure which holds window specification
    struct WindowSpec {
        std::string title;
        u32 width;
        u32 height;
    };


    class Window : public RefCounted{
    public:
        static inline ViewportSize s_ViewportSize{};
        Window() = default;
        Window(WindowSpec& spec);

        ~Window() = default;

        static Ref<Window> Create(WindowSpec spec){return Ref<Window>::Create(spec);}

        bool ShouldClose(){return glfwWindowShouldClose(s_Window);}
        void Loop();
        [[nodiscard]] double getDeltaTime() const { return 1.0/m_Timestep; }

        void SetDeltaTime(double value) {
            m_Timestep = value;
        }

        GLFWwindow* GetHandle() { return s_Window; }
        [[nodiscard]] const auto& GetHandle() const{ return s_Window; }


        bool Good(){return s_Window == NULL;}

        void Close(){
            glfwSetWindowShouldClose(s_Window,GLFW_TRUE);
            Window::closeCallback(s_Window);
        }

        void Update();

        void Clear(float r = 0.2f, float g = 0.3f, float b = 0.4f, float a = 1.0f);
        explicit operator bool(){
            return (s_Window == nullptr);
        }

        VkSurfaceKHR CreateSurface(VkInstance instance);

        WindowSpec& GetSpec(){ return spec; }
        const WindowSpec& GetSpec() const { return spec; }

    private:

        WindowSpec spec;

        static void closeCallback(GLFWwindow* window){

            for (auto& [layerName, layer] : LayerStack::data()) {
                layer->OnWindowShouldCloseEvent();
                layer->SetShouldExit(true);
            }

        }
        static void windowSizeCallback(GLFWwindow* window, int width, int height)
        {
            s_ViewportSize.width = width;
            s_ViewportSize.height = height;
            for(auto& [layerName,layer] : LayerStack::data()){
                layer->OnWindowResizeEvent(width,height);
            }
        }
        static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
            for(auto& [layerName,layer] : LayerStack::data()){
                layer->OnKeyboardEvent(action,key);
            }
        }
        static void windowMouseMoveCallback(GLFWwindow* window, double x,double y){
            for(auto& [layerName,layer] : LayerStack::data()){
                layer->OnMouseMoveEvent((int)x,(int)y);
            }
        }
        static inline GLFWwindow* s_Window = nullptr;
        double m_Timestep{};

    };
}