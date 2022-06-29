//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#include "VertexLayout.h"

namespace FikoEngine{

    FikoEngine::VertexLayout::VertexLayout(std::initializer_list<VertexAttribute> attributes) 
        : attributes{ attributes }
    {

        for (u32 i = 0; i < this->attributes.size(); ++i)
        {
            this->attributes[i].offset = stride;
            stride += static_cast<u32>(ShaderDataType::Size(this->attributes[i].type));
        }
    }
}
