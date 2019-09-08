#include "Window.h"
#include <iostream>

namespace FikoEngine {
    Window::Window(const unsigned int &width, const unsigned int &height, const char *title, WindowMode mode) {
        WindowProps windowProperties;

        windowProperties.Width = width;
        windowProperties.Height = height;
        windowProperties.Title = title;
        windowProperties.Mode = mode;

        m_WindowMaximumWidth = -1;
        m_WindowMaximumHeight = -1;

        Init(windowProperties);
    }

    Window::Window() {
        m_Window = 0;
    }

    Window::~Window() {
    }

    void Window::Init(const WindowProps &props) {
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;
        m_WindowData.Title = props.Title;

        m_Window = glfwCreateWindow(
                props.Mode == WindowMode::Fullscreen ? GetMonitorWidth() : props.Width,
                props.Mode == WindowMode::Fullscreen ? GetMonitorHeight() : props.Height,
                props.Title,
                props.Mode == WindowMode::Fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr
        );
        int code = glfwGetError(NULL);
        if (code != 0) {
            std::cout << code;
            return;
        }

        glfwSetWindowUserPointer(m_Window, &m_WindowData);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
        });
    }

    void Window::Destroy() {
        //		glfwDestroyWindow(m_Window);
    }

    void Window::Create(const unsigned int &width, const unsigned int &height, const char *title, WindowMode mode) {
        WindowProps windowProperties;

        windowProperties.Width = width;
        windowProperties.Height = height;
        windowProperties.Title = title;
        windowProperties.Mode = mode;

        m_WindowMaximumWidth = -1;
        m_WindowMaximumHeight = -1;

        Init(windowProperties);
    }

    void Window::MakeContextCurrent() {
        glfwMakeContextCurrent(m_Window);
    }

    void Window::Event(WindowEvent e) {
        switch (e) {
            case WindowEvent::Close: {
                glfwSetWindowShouldClose(m_Window, GL_TRUE);
                break;
            }

            case WindowEvent::Restore: {
                glfwRestoreWindow(m_Window);
                break;
            }

            case WindowEvent::Minimize: {
                glfwIconifyWindow(m_Window);
                break;
            }

            case WindowEvent::Maximize: {
                glfwMaximizeWindow(m_Window);
                break;
            }

            case WindowEvent::OnFocus: {
                glfwFocusWindow(m_Window);
                break;
            }
        }
    }

    void Window::SetWidth(const unsigned int &width) {
        m_WindowData.Width = width;

        if (m_WindowData.Width > m_WindowMaximumWidth) {
            glfwSetWindowSizeLimits(m_Window, m_WindowMinimumWidth, m_WindowMinimumHeight, m_WindowData.Width,
                                    m_WindowMaximumHeight);
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        } else if (m_WindowData.Width < m_WindowMinimumWidth) {
            glfwSetWindowSizeLimits(m_Window, m_WindowData.Width, m_WindowMinimumHeight, m_WindowMaximumWidth,
                                    m_WindowMaximumHeight);
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        } else {
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        }
    }

    void Window::SetHeight(const unsigned int &height) {
        m_WindowData.Height = height;

        if (m_WindowData.Height > m_WindowMaximumHeight) {
            glfwSetWindowSizeLimits(m_Window, m_WindowMinimumWidth, m_WindowMinimumHeight, m_WindowMaximumWidth,
                                    m_WindowData.Height);
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        } else if (m_WindowData.Height < m_WindowMinimumHeight) {
            glfwSetWindowSizeLimits(m_Window, m_WindowMinimumWidth, m_WindowData.Height, m_WindowMaximumWidth,
                                    m_WindowMaximumHeight);
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        } else {
            glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
        }
    }

    void Window::SetTitle(const char *title) {
        m_WindowData.Title = title;

        glfwSetWindowTitle(m_Window, m_WindowData.Title);
    }

    void Window::SetSizeLimit(const unsigned int &minWidth, const unsigned int &minHeight, const unsigned int &maxWidth,
                              const unsigned int &maxHeight) {
        m_WindowMinimumWidth = minWidth;
        m_WindowMinimumHeight = minHeight;
        m_WindowMaximumWidth = maxWidth;
        m_WindowMaximumHeight = maxHeight;

        glfwSetWindowSizeLimits(m_Window, m_WindowMinimumWidth, m_WindowMinimumHeight, m_WindowMaximumWidth,
                                m_WindowMaximumHeight);
    }

    void Window::SetAspectRatio(const unsigned int &numerator, const unsigned int &denominator) {
        glfwSetWindowAspectRatio(m_Window, numerator, denominator);
    }

    unsigned int Window::GetMonitorWidth() const {
        const GLFWvidmode *VidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        return VidMode->width;
    }

    unsigned int Window::GetMonitorHeight() const {
        const GLFWvidmode *VidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        return VidMode->height;
    }

    int Window::GetKey(int key) {
        if (m_Window != 0)
            return glfwGetKey(this->m_Window, key);

        return -1;
    }

    bool Window::ShouldClose() {
        if (m_Window != 0)
            return glfwWindowShouldClose(m_Window);
        return false;
    }

    void Window::SetWindowShouldClose(int val) {
        glfwSetWindowShouldClose(m_Window, val);
    }

    void Window::Create(const WindowProps &props) {
        Init(props);
    }
}