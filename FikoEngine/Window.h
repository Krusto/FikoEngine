#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
namespace FikoEngine {
        enum class WindowEvent {
            Close = 0,
            Restore = 1,
            Minimize = 2,
            Maximize = 3,
            OnFocus = 4,
        };

        enum class WindowMode {
            Fullscreen = 0,
            Windowed = 1
        };

        enum class WindowSizeLimitParam {
            Width = 0,
            Height = 1
        };

        struct WindowProps {
            unsigned int Width;
            unsigned int Height;
            const char *Title;
            WindowMode Mode;

            WindowProps(unsigned int width = 1280,
                        unsigned int height = 720,
                        const char *title = "OpenGL",
                        WindowMode mode = WindowMode::Windowed)
                    : Width(width), Height(height), Title(title), Mode(mode) {
            }
        };

        class Window {
        private:
            GLFWwindow *m_Window;

            unsigned int m_WindowMinimumWidth;
            unsigned int m_WindowMaximumWidth;
            unsigned int m_WindowMinimumHeight;
            unsigned int m_WindowMaximumHeight;

            struct WindowData {
                unsigned int Width;
                unsigned int Height;
                const char *Title;
            } m_WindowData;


        public:
            Window(const unsigned int &width, const unsigned int &height, const char *title, WindowMode mode);
            Window();
            void Init(const WindowProps &props = WindowProps());

            ~Window();

            void Destroy();

            void Create(const WindowProps &props = WindowProps());
            void Create(const unsigned int &width, const unsigned int &height, const char *title, WindowMode mode);


            void MakeContextCurrent();

            void Event(WindowEvent e);

            void SetWidth(const unsigned int &width);

            void SetHeight(const unsigned int &height);

            void SetTitle(const char *title);

            void SetSizeLimit(const unsigned int &minWidth, const unsigned int &minHeight, const unsigned int &maxWidth,
                              const unsigned int &maxHeight);

            void SetAspectRatio(const unsigned int &numerator, const unsigned int &denominator);

            unsigned int GetMonitorWidth() const;

            unsigned int GetMonitorHeight() const;

            inline unsigned int GetWidth() const { return m_WindowData.Width; }

            inline unsigned int GetHeight() const { return m_WindowData.Height; }

            inline unsigned int GetMinimumSize(WindowSizeLimitParam sParam) const {
                return sParam == WindowSizeLimitParam::Width ? m_WindowMinimumWidth : m_WindowMinimumHeight;
            }

            inline unsigned int GetMaximumSize(WindowSizeLimitParam sParam) const {
                return sParam == WindowSizeLimitParam::Width ? m_WindowMaximumWidth : m_WindowMaximumHeight;
            }

            inline const char *GetTitle() const { return m_WindowData.Title; }

            inline GLFWwindow *GetInstance() const { return m_Window; }

            int GetKey(int key); // SHORTCUT

            bool ShouldClose();

            void SetWindowShouldClose(int val);
        };
}