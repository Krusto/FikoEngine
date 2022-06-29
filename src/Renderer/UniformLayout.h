//
// Created by Stoyanov, Krusto (K.S.) on 6/28/2022.
//
#pragma once

#include "../Core/Core.h"
#include "UniformDataType.h"
namespace FikoEngine{
    struct UniformAttribute {
    public:
        std::string_view name{};
        UniformDataType::UniformType type;
        u32 offset{};
    };

    class UniformLayout {
    public:
        UniformLayout() = default;
        UniformLayout(std::initializer_list<UniformAttribute> attributes);
        UniformLayout(const UniformLayout&) = default;

        std::vector<UniformAttribute> attributes;
        u32 stride{};

        UniformLayout& operator=(const UniformLayout& other) = default;

    };
}