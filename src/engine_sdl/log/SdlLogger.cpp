#include "SdlLogger.h"
#include <SDL_log.h>

SdlLogger::SdlLogger() = default;

void SdlLogger::init() {
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
}

void SdlLogger::i(cstring fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, args);
}

void SdlLogger::d(cstring fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, fmt, args);
}

void SdlLogger::w(cstring fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, fmt, args);
}

void SdlLogger::e(cstring fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt, args);
}


