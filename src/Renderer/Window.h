//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#pragma once
#include "../Core/Core.h"
#include "../Util/Version.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include <vulkan/vulkan.h>
class Window;
struct ApplicationSpec {
    std::string ApplicationName;
    std::string WorkingDirectory;
    FikoEngine::Version AppVersion;
    Window* window;
};

///Structure which holds window specification
struct WindowSpec {
    std::string title;
    u32 width;
    u32 height;
};

class Window {
public:
    Window() = default;

    Window(WindowSpec spec, int argc = 0, char **argv = nullptr);

    static Window *Create(WindowSpec spec, int argc = 0, char **argv = nullptr);

    ~Window();
///Function which is used in the beginning of the main loop
    void Begin();
///Function which is in the main loop
    void Loop();
///Function which is in the end of the main loop
    void End();
///Function which is called whenever we render something
    void OnRender(void (*function)(Timestep &dt));
///Function which is called whenever the mouse is moved
    void OnMouseMove(void (*function)(GLFWwindow *window, double xpos, double ypos));
///Function which is called when there is a keyboard event
    void OnKeyboard(void (*function)(GLFWwindow *window, int key, int scancode, int action, int mods));
///Function which is called when the window is resized
    void OnWindowResize(void (*function)(GLFWwindow *window, int width, int height));
///Function which is called when the user wants to close the window
    void OnWindowClose(void (*function)(GLFWwindow *window));

    auto &getDeltaTime() { return this->mDT; }

    const auto &getDeltaTime() const { return this->mDT; }

    void setDeltaTime(double value) {
        mDT.setTime(value);
    }

    auto &getHandle() { return m_Window; }

    const auto &getHandle() const { return m_Window; }

    bool IsOpen() { return !glfwWindowShouldClose(m_Window); }

    WindowSpec &GetSpec() { return m_WindowSpec; }

    operator GLFWwindow *() { return m_Window; }

    VkSurfaceKHR CreateSurface(VkInstance instance);
private:
    GLFWwindow *m_Window;
    WindowSpec m_WindowSpec;
    Timestep mDT;
};

typedef Window *WindowHandle;
