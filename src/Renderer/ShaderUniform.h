﻿#pragma once
#include <string>
#include <cstdint>

namespace FikoEngine {
    class ShaderResourceDeclaration {
    public:
        ShaderResourceDeclaration() = default;

        ShaderResourceDeclaration(const std::string &name, uint32_t resourceRegister, uint32_t count)
                : m_Name(name), m_Register(resourceRegister), m_Count(count) {}

        virtual const std::string &GetName() const { return m_Name; }

        virtual uint32_t GetRegister() const { return m_Register; }

        virtual uint32_t GetCount() const { return m_Count; }

    private:
        std::string m_Name;
        uint32_t m_Register = 0;
        uint32_t m_Count = 0;
    };
}