#pragma once

#include <string>
#include "../Util/Version.h"

namespace FikoEngine {
struct ApplicationSpec {
    std::string ApplicationName;
    std::string WorkingDirectory;
    Version AppVersion;
};
}