//
// Created by Stoyanov, Krusto (K.S.) on 6/8/2022.
//
#include "Log.h"

namespace FikoEngine
{
    #ifdef LWLOG
    void FikoEngine::Logger::Init() 
    {
        Logger::m_Console = std::make_shared<lwlog::console_logger>("CONSOLE");
        console->set_pattern(".br_red([%T]) .green([%l]): .br_cyan(%v)");
    }
    #else
    void FikoEngine::Logger::Init() {}
    #endif
}
