//
// Created by krusto on 28.08.19 г..
//

#ifndef FIKOENGINE_APPLICATION_H
#define FIKOENGINE_APPLICATION_H

#include "Window.h"
#include "Logger/Logger.h"

namespace FikoEngine {
    class Application {
    public:
        Application();

        void CreateWindow(const char *Title, int width, int height);

        Window GetWindow();

        bool Run();

        virtual ~Application();

        void Loop();

    private:
        mutable Window m_Window;
    };

    Application *CreateApplication();
}
#endif //FIKOENGINE_APPLICATION_H
