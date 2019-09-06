//
// Created by krusto on 30.08.19 г..
//

#ifndef FIKOENGINE_ENTRYPOINT_H
#define FIKOENGINE_ENTRYPOINT_H

#include "Application.h"

extern FikoEngine::Application* FikoEngine::CreateApplication();

int main(int argc,char** argv){
    auto app = FikoEngine::CreateApplication();
    app->Run();
    delete app;
}
#endif //FIKOENGINE_ENTRYPOINT_H
