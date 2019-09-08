//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_ALLOCATIONMANGER_H
#define FIKOENGINE_ALLOCATIONMANGER_H

#include <vulkan/vulkan.h>

namespace FikoEngine::VulkanRenderer {
    class AllocationManger {
    public:
        AllocationManger() {}

        void Init(VkDevice Device);

    private:
        VkDevice mDevice;

    };
}


#endif //FIKOENGINE_ALLOCATIONMANGER_H
