#pragma once

class Sound {
public:
    virtual ~Sound();

    virtual bool isLoaded() const = 0;
};
