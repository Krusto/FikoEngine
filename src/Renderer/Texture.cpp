#include "Texture.h"
#include <Renderer/RendererApi.h>
#include <Renderer/OpenGL/OpenGLTexture.h>
Ref<Texture> Texture::Create(std::string_view Path) {
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        return Ref<OpenGLTexture>::Create(Path);
    default:
        exit(-1);
        break;
    }
}
Ref<Texture> Texture::Create(char* data, uint32_t channels, uint32_t width, uint32_t height) {
    switch (RendererApi::Current()) {
    case RendererApi::API::OpenGL:
        return Ref<OpenGLTexture>::Create(data,channels,width,height);
    default:
        exit(-1);
        break;
    }
}
