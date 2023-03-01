#include "GraphicsContext.h"
#include <Renderer/RendererApi.h>
#include <Renderer/OpenGL/OpenGLContext.h>

Ref<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
{
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        auto context =  Ref<OpenGLContext>::Create(window);
        context->window = window;
        return context;
        break;
    }
    return nullptr;
}
