#include "Shader.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include <Renderer/RendererAPI.h>
namespace FikoEngine {

    Ref<Shader> Shader::Load(const std::string &path) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanShader>::Create(path);
                break;
            default:
                exit(-1);
                break;
        }
        exit(-1);
    }
}