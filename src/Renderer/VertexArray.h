#pragma once
#include <cstdint>
#include <Core/Ref.h>

namespace FikoEngine {

    class VertexArray : public RefCounted {
    public:
        static Ref<VertexArray> Create(uint32_t indexCount);

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        unsigned int IndexCount{};

        uint32_t id() { return m_ID; }

    protected:
        uint32_t m_ID{};
    };
}