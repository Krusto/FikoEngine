//
// Created by Krusto on 21-Oct-22.
//

#pragma once

namespace FikoEngine {
    class VulkanContext {
        static void Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec);
        static void InitImGUI();
    };
}
