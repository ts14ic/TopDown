//
// Created by ts14ic on 12/2/17.
//

#pragma once

// forward declarations begin
class Assets;
class Texture;
struct SDL_Renderer;
struct SDL_Window;
// forward declarations end


class RenderContext {
public:
    virtual ~RenderContext() = 0;

    virtual SDL_Renderer* getRenderer() = 0;

    virtual void render(Texture const& texture, int x, int y) = 0;

    virtual void render(Texture const& texture, int x, int y, float angle) = 0;

    virtual int getScreenWidth() = 0;

    virtual int getScreenHeight() = 0;
};