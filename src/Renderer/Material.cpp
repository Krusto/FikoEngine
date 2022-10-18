#include <Renderer/RendererApi.h>
#include <Renderer/OpenGL/OpenGlMaterial.h>
#include "Material.h"
Ref<Material> Material::Create(const Ref<Shader>& shader, const std::string& name)
{
    switch (RendererApi::Current()) {
        case RendererApi::API::OpenGL:
            return Ref<OpenGLMaterial>::Create(shader,name);
            break;
        default:
            assert(0);
    }
    assert(0);
    return {};
}
