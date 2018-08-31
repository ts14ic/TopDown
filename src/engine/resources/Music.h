#pragma once

class Music {
public:
    virtual ~Music() = 0;

    virtual bool isLoaded() const = 0;
};
