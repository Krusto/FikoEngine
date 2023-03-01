#pragma once
#include <Renderer/GraphicsContext.h>
struct GLFWwindow;

class OpenGLContext :public GraphicsContext {
public:
    OpenGLContext() = default;
    OpenGLContext(GLFWwindow* handle):m_WindowHandle(handle){}
    virtual void Init() override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_WindowHandle;
};