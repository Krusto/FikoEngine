
#include "Surface.h"

VkSurfaceKHR FikoEngine::VulkanRenderer::Surface::getSurface(VkInstance instance,GLFWwindow* win) {
    VkSurfaceKHR surface;
    VkResult result;

#if defined(_LINUX)
    createInfo.setXlibSurfaceCreateInfo(glfwGetX11Display(), glfwGetX11Window(win));
    result = vkCreateXlibSurfaceKHR(instance, createInfo.getXlibSurfaceCreateInfo(), nullptr, &surface);
#endif
#if defined(_WIN32)
    return 0;
#endif

    VK_CHECK(result,"Can not get window surface!");

    return surface;
}
