#include <Renderer/RendererAPI.h>
#include "Material.h"
#include "Renderer/Vulkan/Material.h"

namespace FikoEngine {
    Ref<Material> Material::Create(const Ref<Shader> &shader, const std::string &name) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanMaterial>::Create(shader, name);
                break;
            default:
                assert(0);
        }
        assert(0);
        return {};
    }
}