#pragma once

#include <string>
#include <memory>

/* forward declarations begin */
struct SDL_Point;
struct SDL_Rect;
struct SDL_Texture;

class RenderBase;

/* forward declarations end */

class Texture {
public:
    Texture();

    Texture(RenderBase& engine, char const* path);

    Texture(Texture const&) = delete;

    Texture(Texture&&) = delete;

    void load(RenderBase& engine, char const* path);

    int w() const { return mWidth; }

    int h() const { return mHeight; }

    void render(RenderBase& engine, int x, int y) const;

    void render(RenderBase& engine, int x, int y, float angle) const;

    void render(RenderBase& engine, int x, int y, float angle, int w, int h) const;

    void render(RenderBase& engine, SDL_Point const& pos) const;

    void render(RenderBase& engine, SDL_Point const& pos, float angle) const;

    void render(RenderBase& engine, SDL_Point const& pos, float angle, SDL_Rect const& clip) const;

    void render(RenderBase& engine, SDL_Point const& pos, SDL_Rect const& clip) const;

    struct SDLTextureDeleter {
        void operator()(SDL_Texture* p);
    };

private:
    std::unique_ptr<SDL_Texture, SDLTextureDeleter> mTex;
    int mWidth = 0;
    int mHeight = 0;
};

Texture& textures(std::string const& name);
