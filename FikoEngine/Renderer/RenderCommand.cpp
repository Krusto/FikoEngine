#include "RenderCommand.h"

#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace FikoEngine {

    RendererAPI *RenderCommand::s_RendererAPI = new VulkanRendererAPI();

}