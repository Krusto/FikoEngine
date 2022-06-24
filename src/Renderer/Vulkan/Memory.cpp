#include "Memory.h"
#ifdef __GNUG__
#include <sstream>
#include <string>
#else
#include <format>
#endif

#include "../../Core/Core.h"
#define LOG_MEMORY_INFO 0
namespace FikoEngine{
    void* MemoryAllocateFunc( void*                                       pUserData,
                              size_t                                      size,
                              size_t                                      alignment,
                              VkSystemAllocationScope                     allocationScope){

        void* ptr = malloc(size);//_aligned_malloc(size, alignment);
        memset(ptr, 0, size);
        #if LOG_MEMORY_INFO
        #ifdef __GNUG__
        std::stringstream ss;
        ss << ptr;
        LOG_INFO("pAllocator's allocationFunction: <" + std::string((const char*)pUserData) + ">, size: " + std::to_string(size) +
                 ", alignment: " + std::to_string(alignment) +
                 ", allocationScope: " + std::to_string(allocationScope) +
                 ", return ptr* : " + ss.str());
        #else
        LOG_INFO("pAllocator's allocationFunction: <" + std::format("{}",(const char*)pUserData) + ">, size: " + std::to_string(size) +
                 ", alignment: " + std::to_string(alignment) +
                 ", allocationScope: " + std::to_string(allocationScope) +
                 ", return ptr* : " + std::format("{}",ptr));
        #endif
        #endif
        return ptr;
    }

    void MemoryFreeFunc(void*                                       pUserData,
                        void*                                       pMemory){
#if LOG_MEMORY_INFO
#ifdef __GNUG__
        std::stringstream ss;
        ss << pMemory;
        LOG_INFO("pAllocator's freeFunction: <" + std::string((const char*)pUserData) + "> ptr: " + ss.str());
#else
        LOG_INFO("pAllocator's allocationFunction: <" + std::format("{}",(const char*)pUserData) + ">, size: " + std::to_string(size) +
                 ", alignment: " + std::to_string(alignment) +
                 ", allocationScope: " + std::to_string(allocationScope) +
                 ", return ptr* : " + std::format("{}",ptr));
#endif
#endif
        free(pMemory);
    }
    void* reallocationFunction(void*   pUserData,   void*   pOriginal,  size_t  size, size_t  alignment,  VkSystemAllocationScope allocationScope){
        return realloc(pOriginal, size);
    }

    void internalAllocationNotification(void*   pUserData,  size_t  size,   VkInternalAllocationType allocationType, VkSystemAllocationScope                     allocationScope){

    }

    void internalFreeNotification(void*   pUserData, size_t  size,  VkInternalAllocationType  allocationType, VkSystemAllocationScope                     allocationScope){
    }

    VkAllocationCallbacks* CreatePAllocator(const char* info){
        auto* m_allocator =     (VkAllocationCallbacks*)malloc(sizeof(VkAllocationCallbacks));
        memset(m_allocator, 0, sizeof(VkAllocationCallbacks));
        m_allocator->pUserData = (void*)info;
        m_allocator->pfnAllocation = (PFN_vkAllocationFunction)(&MemoryAllocateFunc);
        m_allocator->pfnReallocation = (PFN_vkReallocationFunction)(&reallocationFunction);
        m_allocator->pfnFree = (PFN_vkFreeFunction)&MemoryFreeFunc;
        m_allocator->pfnInternalAllocation = (PFN_vkInternalAllocationNotification)&internalAllocationNotification;
        m_allocator->pfnInternalFree = (PFN_vkInternalFreeNotification)&internalFreeNotification;
        // storePAllocator(m_allocator);
        return m_allocator;
    }
}