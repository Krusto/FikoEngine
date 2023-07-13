//
// Created by Stoyanov, Krusto (K.S.) on 6/23/2022.
//
#pragma once

#include "../Core/Core.h"
#include "ShaderDataType.h"
namespace FikoEngine{
    struct VertexAttribute {
    public:
        std::string_view name{};
        ShaderUniformType type;
        uint32_t offset{};
    };

    class VertexLayout {
    public:
        VertexLayout() = default;
        VertexLayout(std::initializer_list<VertexAttribute> attributes);
        VertexLayout(const VertexLayout&) = default;

        std::vector<VertexAttribute> attributes;
        uint32_t stride{};

        VertexLayout& operator=(const VertexLayout& other) = default;

    };
}