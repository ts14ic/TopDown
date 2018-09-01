#pragma once

class Graphic;

// TODO Add a fallback texture

/*
 * Texture resource handle
 */
class Texture {
public:
    virtual ~Texture() = 0;

    virtual bool is_loaded() const = 0;

    virtual int get_width() const = 0;

    virtual int get_height() const = 0;
};
