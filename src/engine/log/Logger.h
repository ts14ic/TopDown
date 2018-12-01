#pragma once

#include <utils/typedefs.h>
#include <cstdarg>

class Logger {
public:
    virtual void i(cstring fmt, va_list args) = 0;

    virtual void d(cstring fmt, va_list args) = 0;

    virtual void w(cstring fmt, va_list args) = 0;

    virtual void e(cstring fmt, va_list args) = 0;
};