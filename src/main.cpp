//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//

#include "Core/Core.h"
#include "Application/Application.h"

int main(){
    using namespace FikoEngine;

    Application App(ApplicationSpec{"Example",
                                    "./",
                                    Version{1,0,0}});
    App.Run();

    App.Destroy();

    std::cin.ignore();
    return 0;
}