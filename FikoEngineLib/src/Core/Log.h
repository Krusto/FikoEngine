#pragma once
#include <iostream>
#define LWLOG
#ifdef LWLOG
#include <lwlog.h>
#else
#include <cstdlib>
#endif
namespace FikoEngine {
    class Logger {
    public:
        Logger() {Init(); }
        ~Logger() {Destroy(); };

        void Init();
        void Destroy();

        static void Create();

        static Logger* GetInstance();
#ifdef LWLOG
        std::shared_ptr<lwlog::logger<
                                        lwlog::default_log_policy,
                                        lwlog::default_storage_policy,
                                        lwlog::single_threaded_policy,
                                        lwlog::sinks::stdout_sink
                            >> console;
#endif
    private:
        static std::shared_ptr<Logger> s_Logger;
    };

    class mem {
    public:
        inline static int memsize = 0;
    };

}



#ifdef LWLOG
#define LOG(...) FikoEngine::Logger::GetInstance()->console->info(__VA_ARGS__);std::flush(std::cout);
#define LOG_INFO(...) FikoEngine::Logger::GetInstance()->console->info(__VA_ARGS__);std::flush(std::cout);
#define LOG_ERROR(...) FikoEngine::Logger::GetInstance()->console->error(__VA_ARGS__);std::flush(std::cout);
#define LOG_DEBUG(...) FikoEngine::Logger::GetInstance()->console->debug(__VA_ARGS__);std::flush(std::cout);
#define LOG_WARNING(...) FikoEngine::Logger::GetInstance()->console->warning(__VA_ARGS__);std::flush(std::cout);
#define LOG_CRITICAL(...) FikoEngine::Logger::GetInstance()->console->critical(__VA_ARGS__);std::flush(std::cout);
#else

#define LOG_INFO(...) {std::cout<<(__VA_ARGS__)<<'\n'; \
                        fflush( stdout );}
#define LOG_ERROR(...) {std::cout<<(__VA_ARGS__)<<'\n'; \
                        fflush( stdout );}
#define LOG_DEBUG(...) {std::cout<<(__VA_ARGS__)<<'\n'; \
                        fflush( stdout );}
#define LOG(...) {std::cout<<(__VA_ARGS__)<<'\n'; \
                        fflush( stdout );}
#define LOG_WARNING(...) {std::cout<<(__VA_ARGS__)<<'\n'; \
                        fflush( stdout );}

#endif