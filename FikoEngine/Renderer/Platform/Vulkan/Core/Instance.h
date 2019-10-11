//
// Created by krusto on 9/16/19.
//

#ifndef FIKOENGINE_INSTANCE_H
#define FIKOENGINE_INSTANCE_H


#include <vulkan/vulkan.h>
namespace FikoEngine::VulkanRenderer {
    class Instance {
    public:
        Instance() = default;
        static VkInstance Init(bool debugEnable = false);
    private:
    };
}

#endif //FIKOENGINE_INSTANCE_H
