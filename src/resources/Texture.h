#pragma once

class GraphicContext;

// TODO Add a fallback texture

/*
 * Texture resource handle
 */
class Texture {
public:
    virtual ~Texture() = 0;

    virtual bool isLoaded() const = 0;

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;
};
