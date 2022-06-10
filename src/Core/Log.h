#pragma once
#include <stdlib.h>
#include <lwlog.h>

namespace FikoEngine {
    class Logger {
    public:
        static void Init();

    private:
        static std::shared_ptr<lwlog::console_logger> console;
    };
}

#define LOG_INFO(...) LWLOG_INFO(__VA_ARGS__);fflush( stdout )
#define LOG_ERROR(...) LWLOG_ERROR(__VA_ARGS__);fflush( stdout )
#define LOG_DEBUG(...) LWLOG_DEBUG(__VA_ARGS__);fflush( stdout )
#define LOG(...) LWLOG_INFO(__VA_ARGS__);fflush( stdout )
#define LOG_WARNING(...) LWLOG_WARNING(__VA_ARGS__);fflush(stdout)
