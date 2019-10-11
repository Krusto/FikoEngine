//
// Created by krusto on 9/29/19.
//

#ifndef FIKOENGINE_GRAPHICSPIPELINE_H
#define FIKOENGINE_GRAPHICSPIPELINE_H


#include <string>
#include "../../../../Window.h"

namespace FikoEngine::VulkanRenderer {
    class GraphicsPipeline {
        static void Create(VkDevice logicalDevice,const std::string &VertexShaderPath, const std::string &FragmentShaderPath, FikoEngine::Window *window);
        static void Bind(VkPipeline graphicsPipeline);
    };
}

#endif //FIKOENGINE_GRAPHICSPIPELINE_H
