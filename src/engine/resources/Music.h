#pragma once

class Music {
public:
    virtual ~Music() = 0;

    virtual bool is_loaded() const = 0;
};
