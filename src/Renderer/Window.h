//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#pragma once
#include "../Core/Core.h"
#include "../Util/Version.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include <vulkan/vulkan.h>

namespace FikoEngine 
{
class Window;
    
struct ApplicationSpec 
{
    std::string ApplicationName;
    std::string WorkingDirectory;
    Version AppVersion;
    Window* window;
};

///Structure which holds window specification
struct WindowSpec 
{
    const char* title;
    u32 width;
    u32 height;
};

class Window 
{
public:
    Window() = default;
    Window(WindowSpec spec, int argc = 0, char** argv = nullptr);
    ~Window();
    
public:
    static Window *Create(WindowSpec spec, int argc = 0, char** argv = nullptr);
    VkSurfaceKHR CreateSurface(VkInstance instance);
    
public:
    void Begin();
    void Loop();
    void End();
    void OnRender(void (*function)(Timestep& dt));
    void OnMouseMove(void (*function)(GLFWwindow* window, double xpos, double ypos));
    void OnKeyboard(void (*function)(GLFWwindow* window, int key, int scancode, int action, int mods));
    void OnWindowResize(void (*function)(GLFWwindow* window, int width, int height));
    void OnWindowClose(void (*function)(GLFWwindow* window));

public:
    void SetDeltaTime(double value);
    Timestep& GetDeltaTime();
    const Timestep& GetDeltaTime() const;
    GLFWwindow* GetHandle();
    const GLFWwindow* GetHandle() const;
    bool IsOpen();
    WindowSpec& GetSpec();

public:
    operator GLFWwindow*(){return m_Window;};
    
private:
    GLFWwindow* m_Window{ nullptr };
    WindowSpec m_WindowSpec{};
    Timestep m_DT{};
};

using WindowHandle = Window*;
}
