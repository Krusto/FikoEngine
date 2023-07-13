//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#include "Vertex.h"
#include "ShaderDataType.h"
#include <vulkan/vulkan.h>

namespace FikoEngine{
    VkVertexInputBindingDescription FikoEngine::Vertex::GetBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = Vertex::GetLayout().stride;
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    std::vector<VkVertexInputAttributeDescription> Vertex::GetAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(Vertex::GetLayout().attributes.size());

        for (uint32_t i = 0; i < attributeDescriptions.size(); ++i) {
            attributeDescriptions[i].binding = 0;
            attributeDescriptions[i].location = i;
            attributeDescriptions[i].format = ShaderDataType::Format(Vertex::GetLayout().attributes[i].type);
            attributeDescriptions[i].offset = Vertex::GetLayout().attributes[i].offset;
        }

        return attributeDescriptions;
    }
}
