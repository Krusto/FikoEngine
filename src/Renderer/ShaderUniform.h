#pragma once
#include <string>
#include <cstdint>

namespace FikoEngine {
    class ShaderResourceDeclaration {
    public:
        ShaderResourceDeclaration() = default;

        ShaderResourceDeclaration(const std::string &name, u32 resourceRegister, u32 count)
                : m_Name(name), m_Register(resourceRegister), m_Count(count) {}

        virtual const std::string &GetName() const { return m_Name; }

        virtual u32 GetRegister() const { return m_Register; }

        virtual u32 GetCount() const { return m_Count; }

    private:
        std::string m_Name;
        u32 m_Register = 0;
        u32 m_Count = 0;
    };
}