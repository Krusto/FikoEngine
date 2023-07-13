#include <Renderer/RendererAPI.h>
#include "Material.h"
#include "Renderer/Vulkan/Material.h"
#include "Renderer/OpenGL/OpenGLMaterial.h"

namespace FikoEngine {
    Material* Material::Create(WeakRef<Shader> shader,std::string_view name) {
        switch (RendererAPI::Current()) {
              case RendererAPI::API::Vulkan:
                return new VulkanMaterial(shader, name);
            case RendererAPI::API::OpenGL:
                return new OpenGLMaterial(shader,name);
            default:
                return nullptr;
        }
    }
}