//
// Created by Stoyanov, Krusto (K.S.) on 6/7/2022.
//
#include "Renderer.h"
#include "RendererAPI.h"
namespace FikoEngine {
    void Renderer::Init(RendererSpec rendererSpec,ApplicationSpec applicationSpec) {
        m_RendererSpec = rendererSpec;
        RendererAPI::Init({rendererSpec.SurfaceWidth, rendererSpec.SurfaceHeight}, applicationSpec);
    }
    void Renderer::Draw(){
        RendererAPI::Draw();
    }
    void Renderer::Destroy(){
        RendererAPI::Destroy();
    }
}