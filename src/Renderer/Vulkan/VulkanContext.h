//
// Created by Krusto on 21-Oct-22.
//

#pragma once

#include "Renderer/Window.h"
#include "RendererData.h"
#include "Renderer/Renderer.h"

namespace FikoEngine {
    class VulkanContext {
    public:

        static void Init(RendererSpec& rendererSpec, ApplicationSpec applicationSpec);
        static void InitImGUI();

        inline static RendererDataAPI s_RendererData;
    private:
        inline static VkDescriptorPool s_ImGUI_Descriptorpool;
    };
}
