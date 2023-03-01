#pragma once
#include <Renderer/Renderer.h>
#include <Renderer/RendererApi.h>
class OpenGLRenderer : public RendererApi {
public:
    OpenGLRenderer() = default;
    virtual void Init() override {};
    virtual void Shutdown() override {};
    virtual void BeginFrame() override {};
    virtual void EndFrame() override {};
    virtual void RenderQuad() override {};
    virtual void RenderMesh() override {};
    virtual void RenderMeshWithMaterial() override {};
    virtual void ClearColor(glm::vec4 color) override;
    virtual void DrawIndexed(Ref<VertexArray>& va) override;
    virtual void DrawQuad2D(glm::vec2 position, glm::vec2 size, glm::vec3 color) override;
private:
};