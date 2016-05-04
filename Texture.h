#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>

/* forward declarations begin */
struct SDL_Point;
struct SDL_Rect;
struct SDL_Texture;
/* forward declarations end */

struct FailedToLoadTextureException {};

class Texture {
public:
    Texture();
    Texture(char const* path);
    ~Texture();
    
    Texture(Texture const&) = delete;
    Texture(Texture&&) = delete;
    
    void load(char const* path);
    
    int w() const { return _w; }
    int h() const { return _h; }

    void render(int x, int y) const;
    void render(int x, int y, float angle) const;
    void render(int x, int y, float angle, int w, int h) const;
    
    void render(SDL_Point const& pos) const;
    void render(SDL_Point const& pos, float angle) const;
    void render(SDL_Point const& pos, float angle, SDL_Rect const& clip) const;
    void render(SDL_Point const& pos, SDL_Rect const& clip) const;

private:
    SDL_Texture* _tex = nullptr;
    int _w = 0;
    int _h = 0;
};

Texture& textures(std::string const& name);

#endif // TEXTURE_H_INCLUDED
