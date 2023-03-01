#include "Shader.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/OpenGL/OpenGLShader.h"
#include <Renderer/RendererAPI.h>
namespace FikoEngine {

    Ref<Shader> Shader::Load(const std::string &path) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanShader>::Create(path);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLShader>::Create(path,false);
            default:
                return nullptr;
        }
    }
}