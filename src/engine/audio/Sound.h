#pragma once

class Sound {
public:
    virtual ~Sound();

    virtual bool is_loaded() const = 0;
};
