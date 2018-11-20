#pragma once

#include <cstddef>

class ClockEngine {
public:
    ~ClockEngine();

    virtual std::size_t get_current_time() const = 0;
};
