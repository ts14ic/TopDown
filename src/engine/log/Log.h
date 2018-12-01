#pragma once

#include "Logger.h"

class Log {
public:
    static void install_logger(Logger& logger);

    static void uninstall_logger(Logger& logger);

    static void i(cstring fmt, ...);

    static void d(cstring fmt, ...);

    static void w(cstring fmt, ...);

    static void e(cstring fmt, ...);
};