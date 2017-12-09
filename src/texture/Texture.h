#pragma once

#include <string>
#include <memory>

/* forward declarations begin */
struct SDL_Point;
struct SDL_Rect;
struct SDL_Texture;

class RenderContext;

/* forward declarations end */

/* TODO separate responsibilities
 * current responsibilities:
 * 1. loading
 * 2. texture info
 * 3. rendering
 */
class Texture {
public:
    Texture();

    Texture(RenderContext& engine, char const* path);

    Texture(Texture const&) = delete;

    Texture(Texture&&) = delete;

    void load(RenderContext& engine, char const* path);

    bool isLoaded() const;

    int getWidth() const { return mWidth; }

    int getHeight() const { return mHeight; }

    SDL_Texture* getWrapped() const;

private:
    struct SDLTextureDeleter {
        void operator()(SDL_Texture* p);
    };

private:

    std::unique_ptr<SDL_Texture, SDLTextureDeleter> mTex;
    int mWidth = 0;
    int mHeight = 0;
};
