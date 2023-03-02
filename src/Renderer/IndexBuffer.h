#pragma once
#include <cstdint>
#include <Core/Ref.h>

namespace FikoEngine {
    class IndexBuffer : public RefCounted {
    public:
        static Ref<IndexBuffer> Create(const u32 *data, u32 length);

        virtual void Bind() const = 0;

        u32 indexCount{};
    protected:
        u32 m_ID;
    };
}