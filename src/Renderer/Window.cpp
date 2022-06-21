#include "Window.h"
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "Vulkan/Memory.h"
#include <vulkan/vulkan.h>
#ifdef _WIN32
#include <vulkan/vulkan_win32.h>
#endif

namespace FikoEngine {
Window::Window(WindowSpec spec, int argc, char **argv) {
    if (!glfwInit()) {
        LOG_ERROR("GLFW CAN NOT INITALIZE!!!");
        exit(-1);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    this->m_Window = glfwCreateWindow(spec.width, spec.height, spec.title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(0);
    glfwSetWindowShouldClose(m_Window, 0);
    m_WindowSpec = spec;
}

Window *Window::Create(WindowSpec spec, int argc, char **argv) {
    return new Window(spec, argc, argv);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
}

void Window::Begin() {
    glfwPollEvents();
}

void Window::Loop() {

/*sf::Event event;
while (m_Window.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::EventType::MouseMoved:
        (*this->onMouseMove)(mDT, event.mouseMove.x, event.mouseMove.y);
        break;
    case sf::Event::EventType::KeyPressed:
        (*this->onKeyboard)(event.key.code , event.mouseMove.x,event.mouseMove.y);
        break;
    case sf::Event::EventType::Resized:
        (*this->onWindowResize)(event.size.width, event.size.height);
    case sf::Event::EventType::Closed:
        this->m_Window.close();
    }
}

(*this->onRender)(mDT);*/

}

void Window::End() {
}

void Window::OnRender(void(*function)(Timestep &dt)) {
}

void Window::OnMouseMove(void(*function)(GLFWwindow *window, double xpos, double ypos)) {
    glfwSetCursorPosCallback(this->m_Window, *function);
}

void Window::OnKeyboard(void(*function)(GLFWwindow *window, int key, int scancode, int action, int mods)) {
    glfwSetKeyCallback(this->m_Window, function);
}

void Window::OnWindowResize(void(*function)(GLFWwindow *window, int width, int height)) {
    glfwSetWindowSizeCallback(this->m_Window, function);
}

void Window::OnWindowClose(void(*function)(GLFWwindow *window)) {
    glfwSetWindowCloseCallback(this->m_Window, function);
}
VkSurfaceKHR Window::CreateSurface(VkInstance instance) {
    VkSurfaceKHR surface;
    #ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(m_Window);
    createInfo.hinstance = GetModuleHandle(nullptr);
    vkCreateWin32SurfaceKHR(instance,&createInfo,CreatePAllocator("Surface"),&surface);
    #endif
    return surface;
}
}