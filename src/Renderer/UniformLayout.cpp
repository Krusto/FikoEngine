//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#include "UniformLayout.h"
#include "../Core/Core.h"
namespace FikoEngine
{
    FikoEngine::UniformLayout::UniformLayout(std::initializer_list<UniformAttribute> attributes) 
        : attributes{ attributes }
    {
        for (auto& [name, type, offset] : this->attributes)
        {
            offset = stride;
            stride += static_cast<u32>(UniformDataType::Size(type));
        }
    }
}
