//
// Created by Krusto on 21-Oct-22.
//

#pragma once

#include "Renderer/Window.h"
#include "RendererData.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

namespace FikoEngine {
    class VulkanRenderer : public RendererAPI{
    public:

        virtual void Init(RendererSpec rendererSpec, ApplicationSpec applicationSpec) override;
        virtual void InitImGUI(WeakRef<Window> window) override;

        virtual void Shutdown() override;
        virtual void BeginFrame() override;
        virtual void EndFrame() override;
        virtual void RenderQuad() override{};
        virtual void RenderMesh() override {}
        virtual void RenderMeshWithMaterial() override {}
        virtual void ClearColor(glm::vec4 color) override {}
        virtual void DrawIndexed(Ref<VertexArray>& va) override;
        virtual void DrawQuad2D(glm::vec2 position, glm::vec2 size, glm::vec3 color) override {}

        inline static RendererDataAPI s_RendererData;
    private:
        uint32_t imageIndex;

        inline static VkDescriptorPool s_ImGUI_Descriptorpool;
    };
}
