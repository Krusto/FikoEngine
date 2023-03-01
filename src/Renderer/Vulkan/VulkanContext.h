#pragma once
#include <Renderer/GraphicsContext.h>
struct GLFWwindow;

class VulkanContext :public GraphicsContext {
public:
    VulkanContext() = default;
    VulkanContext(GLFWwindow* handle):m_WindowHandle(handle){}
    virtual void Init() override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_WindowHandle;
};