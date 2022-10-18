#pragma once
#ifdef LWLOG
#include <lwlog.h>
#else
#include <iostream>
#include <cstdlib>
#endif
namespace FikoEngine {
    class Logger {
    public:
        static void Init();

#ifdef LWLOG
        static std::shared_ptr<lwlog::console_logger> console;
#endif
    };
}

#ifdef LWLOG
#define LOG(...) FikoEngine::Logger::console->info(__VA_ARGS__)
#define LOG_INFO(...) FikoEngine::Logger::console->info(__VA_ARGS__)
#define LOG_ERROR(...) FikoEngine::Logger::console->error(__VA_ARGS__)
#define LOG_DEBUG(...) FikoEngine::Logger::console->debug(__VA_ARGS__)
#define LOG_WARNING(...) FikoEngine::Logger::console->warning(__VA_ARGS__)
#define LOG_CRITICAL(...) FikoEngine::Logger::console->critical(__VA_ARGS__)
#else
#define LOG_INFO(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_ERROR(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_DEBUG(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_WARNING(...) std::cout<<(__VA_ARGS__)<<'\n';fflush(stdout)
#endif