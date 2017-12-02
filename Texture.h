#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include <memory>

/* forward declarations begin */
struct SDL_Point;
struct SDL_Rect;
struct SDL_Texture;

class EngineBase;

/* forward declarations end */

class Texture {
public:
    Texture();

    Texture(EngineBase& engine, char const* path);

    Texture(Texture const&) = delete;

    Texture(Texture&&) = delete;

    void load(EngineBase& engine, char const* path);

    int w() const { return mWidth; }

    int h() const { return mHeight; }

    void render(EngineBase& engine, int x, int y) const;

    void render(EngineBase& engine, int x, int y, float angle) const;

    void render(EngineBase& engine, int x, int y, float angle, int w, int h) const;

    void render(EngineBase& engine, SDL_Point const& pos) const;

    void render(EngineBase& engine, SDL_Point const& pos, float angle) const;

    void render(EngineBase& engine, SDL_Point const& pos, float angle, SDL_Rect const& clip) const;

    void render(EngineBase& engine, SDL_Point const& pos, SDL_Rect const& clip) const;

    struct SDLTextureDeleter {
        void operator()(SDL_Texture* p);
    };

private:
    std::unique_ptr<SDL_Texture, SDLTextureDeleter> mTex;
    int mWidth = 0;
    int mHeight = 0;
};

Texture& textures(std::string const& name);

#endif // TEXTURE_H_INCLUDED
