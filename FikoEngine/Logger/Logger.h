//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_LOGGER_H
#define FIKOENGINE_LOGGER_H

#include <memory>
#include <iostream>

class Log
{
public:
    static void Init()
    {
    }

private:
};

#define FIKO_CORE_INFO(...)     std::cout<<__VA_ARGS__<<std::endl;
#define FIKO_CORE_WARNING(...)  std::cout<<__VA_ARGS__;
#define FIKO_CORE_ERROR(...)    std::cout<<__VA_ARGS__<<std::endl;
#define FIKO_CORE_CRITICAL(...) std::cout<<__VA_ARGS__;
#define FIKO_CORE_DEBUG(...) std::cout<<__VA_ARGS__;
#endif //FIKOENGINE_LOGGER_H
