#pragma once

#include <stdarg.h>

class Logger {
public:
    virtual void i(const char* fmt, va_list args) = 0;

    virtual void d(const char* fmt, va_list args) = 0;

    virtual void w(const char* fmt, va_list args) = 0;

    virtual void e(const char* fmt, va_list args) = 0;
};