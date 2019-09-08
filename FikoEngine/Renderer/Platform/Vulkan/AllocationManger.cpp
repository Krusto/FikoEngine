#include "AllocationManger.h"

namespace FikoEngine::VulkanRenderer {
    void AllocationManger::Init(VkDevice Device) {
        mDevice = Device;
    }
}