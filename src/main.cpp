//
// Created by KSTOYAN2 on 6/3/2022.
//
#include <iostream>
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