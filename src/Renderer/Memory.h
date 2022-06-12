//
// Created by KSTOYAN2 on 6/7/2022.
//
#include <vulkan/vulkan.h>

namespace FikoEngine{
    void* MemoryAllocateFunc( void*                                       pUserData,
                              size_t                                      size,
                              size_t                                      alignment,
                              VkSystemAllocationScope                     allocationScope);

    void MemoryFreeFunc(void*                                       pUserData,
                        void*                                       pMemory);

    VkAllocationCallbacks* CreatePAllocator(const char* info);
}