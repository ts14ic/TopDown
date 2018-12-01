#include "Log.h"

#include <SDL_log.h>
#include <unordered_set>

static Logger* LOGGER = nullptr;

void Log::install_logger(Logger& logger) {
    LOGGER = &logger;
}

void Log::uninstall_logger(Logger& logger) {
    if (LOGGER == &logger) {
        LOGGER = nullptr;
    }
}

void Log::i(cstring fmt, ...) {
    if (LOGGER != nullptr) {
        va_list args;
        va_start(args, fmt);
        LOGGER->i(fmt, args);
        va_end(args);
    }
}

void Log::d(cstring fmt, ...) {
    if (LOGGER != nullptr) {
        va_list args;
        va_start(args, fmt);
        LOGGER->d(fmt, args);
        va_end(args);
    }
}

void Log::w(cstring fmt, ...) {
    if (LOGGER != nullptr) {
        va_list args;
        va_start(args, fmt);
        LOGGER->w(fmt, args);
        va_end(args);
    }
}

void Log::e(cstring fmt, ...) {
    if (LOGGER != nullptr) {
        va_list args;
        va_start(args, fmt);
        LOGGER->e(fmt, args);
        va_end(args);
    }
}
