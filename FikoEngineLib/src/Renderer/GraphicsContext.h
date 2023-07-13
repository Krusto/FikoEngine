﻿#pragma once
#include <Core/Ref.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"

class GraphicsContext : public RefCounted{
public:
    static GraphicsContext* Create(GLFWwindow* window);

    virtual ~GraphicsContext() {};

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

    GLFWwindow* window;
    
    static GraphicsContext* s_Context;
};

