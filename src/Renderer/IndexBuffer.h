#pragma once
#include <cstdint>
#include <Core/Ref.h>

namespace FikoEngine {
    class IndexBuffer : public RefCounted {
    public:
        static Ref<IndexBuffer> Create(const uint32_t *data, uint32_t length);

        virtual void Bind() const = 0;

        uint32_t indexCount{};
    protected:
        uint32_t m_ID;
    };
}