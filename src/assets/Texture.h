#pragma once

/* forward declarations begin */
struct SDL_Texture;

class RenderContext;

/* forward declarations end */

/* TODO separate responsibilities
 * current responsibilities:
 * 1. loading
 * 2. texture info
 *
 * TODO Add a "missing texture" texture
 */
class Texture {
public:
    virtual ~Texture() = 0;

    virtual void load(RenderContext& engine, char const* path) = 0;

    virtual bool isLoaded() const = 0;

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

    virtual SDL_Texture* getWrapped() const = 0;
};
