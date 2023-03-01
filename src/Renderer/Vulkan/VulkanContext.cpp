#include "VulkanContext.h"

void VulkanContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
}

void VulkanContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
    glfwPollEvents();
}
