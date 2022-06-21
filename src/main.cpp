//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//
#include "Core/Core.h"
#ifdef _WIN32
#include <conio.h>
#endif
#include "Application/Application.h"

int main(){
    using namespace FikoEngine;

    Application App(ApplicationSpec{"Example",
                                    "./",
                                    Version{1,0,0}});
    if(!App.Run()){

    }

    App.Destroy();
    return 0;
}