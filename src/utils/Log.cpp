#include "utils/Log.h"

std::ostream& Log::defaultOStream = std::cout;

void Log::info(const char* message) {
    defaultOStream << "[info] " << message << std::endl;
}

void Log::warn(const char* message) {
    defaultOStream << "\033[0;33m[warning] " << message << "\033[0m" << std::endl;
}

void Log::error(int errorCode, const char* message) {
    defaultOStream << "\033[1;31m[error] " << message << "\033[0m" << std::endl;
    std::exit(errorCode);
}