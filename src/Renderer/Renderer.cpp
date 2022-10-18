//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Renderer.h"
#include "RendererAPI.h"
namespace FikoEngine {
    void Renderer::Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec) {
        m_RendererSpec = rendererSpec;
        RendererAPI::Init({rendererSpec.SurfaceSize.x, rendererSpec.SurfaceSize.y}, applicationSpec);
    }
    void Renderer::Draw(){
        RendererAPI::Draw();
    }
    void Renderer::Destroy(){
        RendererAPI::Destroy();
    }
    void Renderer::ResizeFramebuffer(ViewportSize size){
        RendererAPI::ResizeFramebuffer(size);
    }

}