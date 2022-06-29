//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#include "Vertex.h"
#include "ShaderDataType.h"
#include <vulkan/vulkan.h>

namespace FikoEngine
{
    VertexLayout Vertex::GetLayout() 
    { 
        return { 
            { "Position", ShaderDataType::ShaderType::vec3 }, 
            { "Color", ShaderDataType::ShaderType::vec3 } 
        };
    }
    
    VkVertexInputBindingDescription Vertex::GetBindingDescription() 
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = this->GetLayout().stride;
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    std::vector<VkVertexInputAttributeDescription> Vertex::GetAttributeDescriptions() 
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(this->GetLayout().attributes.size());

        for (u32 i = 0; i < attributeDescriptions.size(); ++i) 
        {
            attributeDescriptions[i].binding = 0;
            attributeDescriptions[i].location = i;
            attributeDescriptions[i].format = ShaderDataType::Format(this->GetLayout().attributes[i].type);
            attributeDescriptions[i].offset = this->GetLayout().attributes[i].offset;
        }

        return attributeDescriptions;
    }
}
