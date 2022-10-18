#include "Shader.h"
#include <Renderer/RendererAPI.h>
namespace FikoEngine {

    Ref<Shader> Shader::Load(const std::string &path) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                break;
            default:
                exit(-1);
                break;
        }
    }
}