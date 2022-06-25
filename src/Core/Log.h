#pragma once
//#define DISABLE_LOG

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

    private:
#ifdef LWLOG
        inline static std::shared_ptr<lwlog::console_logger> console{};
#endif
    };
}
#ifdef DISABLE_LOG
#define LOG_INFO(...)
#define LOG_ERROR(...)
#define LOG_DEBUG(...)
#define LOG(...)
#define LOG_WARNING(...)
#else
#ifdef LWLOG
#define LOG_INFO(...) LWLOG_INFO(__VA_ARGS__);fflush( stdout )
#define LOG_ERROR(...) LWLOG_ERROR(__VA_ARGS__);fflush( stdout )
#define LOG_DEBUG(...) LWLOG_DEBUG(__VA_ARGS__);fflush( stdout )
#define LOG(...) LWLOG_INFO(__VA_ARGS__);fflush( stdout )
#define LOG_WARNING(...) LWLOG_WARNING(__VA_ARGS__);fflush(stdout)
#else
#define LOG_INFO(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_ERROR(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_DEBUG(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG(...) std::cout<<(__VA_ARGS__)<<'\n';fflush( stdout )
#define LOG_WARNING(...) std::cout<<(__VA_ARGS__)<<'\n';fflush(stdout)
#endif
#endif
