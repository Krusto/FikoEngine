#pragma once
#include <Core/Ref.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GraphicsContext : public RefCounted{
public:
    static Ref<GraphicsContext> Create(GLFWwindow* window);
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

    GLFWwindow* window;
    
    inline static Ref<GraphicsContext> s_Context;
};

