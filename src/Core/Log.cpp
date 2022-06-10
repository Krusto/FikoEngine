//
// Created by KSTOYAN2 on 6/8/2022.
//
#pragma once
#include <lwlog.h>
#include "Log.h"

namespace FikoEngine{
    std::shared_ptr<lwlog::console_logger> Logger::console;
    void FikoEngine::Logger::Init() {
        Logger::console = std::make_shared<lwlog::console_logger>("CONSOLE");
        LWLOG_SET_PATTERN(".br_red([%T]) .green([%l]): .br_cyan(%v)");
    }
}