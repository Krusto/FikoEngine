//
// Created by krusto on 10/11/19.
//

#ifndef FIKOENGINE_OPENGLCORE_H
#define FIKOENGINE_OPENGLCORE_H

#include "../../../Window.h"

namespace FikoEngine::OpenGLRenderer {
    class OpenGLCore {
    public:
        OpenGLCore() = default;
        void Init(FikoEngine::Window window);

        void Begin();
        void End();

        ~OpenGLCore();
    };
}

#endif //FIKOENGINE_OPENGLCORE_H
