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

    struct WindowSpec {
        std::string title;
        u32 width;
        u32 height;
    };


    class Window : public RefCounted{
    public:
        Window() = default;
        Window(WindowSpec& spec);

        ~Window() = default;

        static Ref<Window> Create(WindowSpec spec){return Ref<Window>::Create(spec);}

    public:
        void Update();

        bool ShouldClose(){return glfwWindowShouldClose(s_Window);}

        double GetDeltaTime() const;
        void SetDeltaTime(double value);

        GLFWwindow* GetHandle() { return s_Window; }

        bool Good();

        void Close();

        void Clear(float r = 0.2f, float g = 0.3f, float b = 0.4f, float a = 1.0f);

        WindowSpec& GetSpec(){ return spec; }
        const WindowSpec& GetSpec() const { return spec; }

        VkSurfaceKHR CreateSurface(VkInstance instance);

    public:
        static inline ViewportSize s_ViewportSize{};

    public:
        operator bool();

    private:
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
    private:
        static inline GLFWwindow* s_Window = nullptr;

        WindowSpec spec;
        double m_Timestep{};
    };
}