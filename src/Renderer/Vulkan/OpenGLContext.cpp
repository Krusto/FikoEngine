#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

#include <iostream>

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
    glfwPollEvents();
}
