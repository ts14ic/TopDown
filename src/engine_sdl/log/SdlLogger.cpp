#include "SdlLogger.h"
#include <SDL_log.h>

SdlLogger::SdlLogger() {
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
}

void SdlLogger::i(const char* fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, args);
}

void SdlLogger::d(const char* fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, fmt, args);
}

void SdlLogger::w(const char* fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, fmt, args);
}

void SdlLogger::e(const char* fmt, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt, args);
}


