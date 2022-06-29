//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#pragma once
#include "../Core/Math.h"
#include "UniformLayout.h"

namespace FikoEngine{
    struct MVPUniform{
        alignas(16) mat4 model;
        alignas(16) mat4 view;
        alignas(16) mat4 projection;
        static UniformLayout GetLayout() { return {{"Model",UniformDataType::UniformType::mat4},
                                                   {"View",UniformDataType::UniformType::mat4},
                                                   {"Projection",UniformDataType::UniformType::mat4}};}
    };
}