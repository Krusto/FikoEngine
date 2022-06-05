//
// Created by KSTOYAN2 on 6/3/2022.
//

#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include <functional>
#include "Definitions.h"

struct Timestep{
    void setTime(float t){}
};
struct WindowSpec{
    std::string title;
    uint32 width;
    uint32 height;
};
class Window {
public:
    Window() = default;
    Window(WindowSpec spec, int argc = 0, char** argv = nullptr);
    static Window* Create(WindowSpec spec, int argc = 0, char** argv = nullptr);
    ~Window();

    void Begin();
    void Loop();
    void End();

    void OnRender(void (*function)(Timestep& dt));
    void OnMouseMove(void (*function)(GLFWwindow* window, double xpos, double ypos));
    void OnKeyboard(void (*function)(GLFWwindow* window, int key, int scancode, int action, int mods));
    void OnWindowResize(void (*function)(GLFWwindow* window,int width, int height));
    void OnWindowClose(void (*function)(GLFWwindow* window));
    auto& getDeltaTime() { return this->mDT; }
    const auto& getDeltaTime() const { return this->mDT; }

    void setDeltaTime(double value) {
        mDT.setTime(value);
    }

    auto& getHandle() { return m_Window; }
    const auto& getHandle() const{ return m_Window; }

    bool IsOpen() { return !glfwWindowShouldClose(m_Window); }

    WindowSpec& GetSpec(){return m_WindowSpec;}
    
    operator GLFWwindow* () { return m_Window; }
private:
    GLFWwindow* m_Window;
    WindowSpec m_WindowSpec;
    Timestep mDT;
};

typedef Window* WindowHandle;
