//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <glm/glm.hpp>
#include "VertexLayout.h"

namespace FikoEngine
{
    class Vertex // Shouldn't be a struct, since it's not a POD
    {
        public:
            static VertexLayout GetLayout();
            static VkVertexInputBindingDescription GetBindingDescription();
            static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
        
        public:
            glm::vec3 pos;
            glm::vec3 color;
    };
}
