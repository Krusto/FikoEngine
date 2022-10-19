#include "Texture.h"
#include <Renderer/RendererAPI.h>
#include <Renderer/OpenGL/OpenGLTexture.h>
Ref<Texture> Texture::Create(std::string_view Path) {
    switch (RendererAPI::Current()) {
    case RendererAPI::API::OpenGL:
        return Ref<OpenGLTexture>::Create(Path);
    default:
        exit(-1);
        break;
    }
}
Ref<Texture> Texture::Create(char* data, uint32_t channels, uint32_t width, uint32_t height) {
    switch (RendererAPI::Current()) {
    case RendererAPI::API::OpenGL:
        return Ref<OpenGLTexture>::Create(data,channels,width,height);
    default:
        exit(-1);
        break;
    }
}
