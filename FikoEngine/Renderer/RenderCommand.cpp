#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FikoEngine {

    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}