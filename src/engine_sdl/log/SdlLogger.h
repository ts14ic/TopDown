#pragma once

#include <engine/log/Logger.h>

class SdlLogger : public Logger {
public:
    SdlLogger();

    void init();

    void i(cstring fmt, va_list args) override;

    void d(cstring fmt, va_list args) override;

    void w(cstring fmt, va_list args) override;

    void e(cstring fmt, va_list args) override;
};