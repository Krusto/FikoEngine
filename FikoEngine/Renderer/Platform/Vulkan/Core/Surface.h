#ifndef FIKOENGINE_SURFACE_H
#define FIKOENGINE_SURFACE_H
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "../VulkanUtilities.h"
#include <vulkan/vulkan.h>

namespace FikoEngine::VulkanRenderer {
    class Surface {
    public:
        static VkSurfaceKHR getSurface(VkInstance instance,GLFWwindow* window);
    };
}

#endif //FIKOENGINE_SURFACE_H
