//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <glm/glm.hpp>
#include "VertexLayout.h"

namespace FikoEngine{
    struct Vertex{
        glm::vec3 pos;
        glm::vec3 color;

        static VertexLayout GetLayout() { return {{"Position",ShaderDataType::ShaderType::vec3},{"Color",ShaderDataType::ShaderType::vec3}};}
        static VkVertexInputBindingDescription GetBindingDescription();

        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
    };
}