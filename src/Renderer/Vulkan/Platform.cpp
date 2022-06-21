#include "Platform.h"
namespace FikoEngine {
    std::vector<const char *> GetPlatformExtensions() {
        std::vector<const char *> extensions;
        #ifdef _WIN32
            LOG("Current platform is Windows!");
            extensions.emplace_back("VK_KHR_win32_surface");
        #elif LINUX
            LOG("Current platform is Linux!");
            extensions.emplace_back("VK_KHR_xlib_surface");
        #endif
        return extensions;
    }
}