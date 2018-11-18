#pragma once

#include "Logger.h"

class Log {
public:
    static void install_logger(Logger& logger);

    static void uninstall_logger(Logger& logger);

    static void i(const char* fmt, ...);

    static void d(const char* fmt, ...);

    static void w(const char* fmt, ...);

    static void e(const char* fmt, ...);
};