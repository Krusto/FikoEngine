﻿#include "IndexBuffer.h"
#include <Core/Ref.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/Vulkan/IndexBuffer.h>

namespace FikoEngine {

    Ref<IndexBuffer> IndexBuffer::Create(const uint32_t *data, uint32_t length) {
        switch (RendererAPI::Current()) {
            case RendererAPI::API::Vulkan:
                return Ref<VulkanIndexBuffer>::Create(data, length);
                break;
            default:
                assert(0);
                break;
        }
        assert(0);
        return {};
    }
}