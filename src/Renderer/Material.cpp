#include <Renderer/RendererAPI.h>
#include "Material.h"
#include "Renderer/Vulkan/Material.h"
#include "Renderer/OpenGL/OpenGLMaterial.h"

namespace FikoEngine {
    Ref<Material> Material::Create(const Ref<Shader> &shader, const std::string &name) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanMaterial>::Create(shader, name);
            case RendererAPI::API::OpenGL:
                return Ref<OpenGLMaterial>::Create(shader,name);
            default:
                return nullptr;
        }
    }
}