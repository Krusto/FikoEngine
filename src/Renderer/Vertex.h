//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once
#include <glm/glm.hpp>
#include "VertexLayout.h"

namespace FikoEngine{
    struct Vertex{
        glm::vec3 pos;
<<<<<<< HEAD
        glm::vec3 normal;
        glm::vec2 texCoord;

        static VertexLayout GetLayout() { return {{"Position",ShaderUniformType::Vec3},{"Normal",ShaderUniformType::Vec3},{"TextureCoord",ShaderUniformType::Vec2}};}
=======
        glm::vec3 color;
        //glm::vec2 texCoord;

        static VertexLayout GetLayout() { return {{"Position",ShaderUniformType::Vec3},{"Color",ShaderUniformType::Vec3}};}//,{"TextureCoord",ShaderUniformType::Vec2}};}
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
        static VkVertexInputBindingDescription GetBindingDescription();

        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
    };
}