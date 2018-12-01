#pragma once

#include <engine/log/Logger.h>

class SdlLogger : public Logger {
public:
    SdlLogger();

    void init();

    void i(const char* fmt, va_list args) override;

    void d(const char* fmt, va_list args) override;

    void w(const char* fmt, va_list args) override;

    void e(const char* fmt, va_list args) override;
};