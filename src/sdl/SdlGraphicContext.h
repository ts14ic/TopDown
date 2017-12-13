//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/GraphicContext.h"

class Texture;

class SdlTexture;

struct SDL_Renderer;
struct SDL_Window;

class SdlGraphicContext : public GraphicContext {
public:
    void refreshScreen() override;

    void clearScreen() override;

    void renderBox(const Box& box, const Color& color) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    void setSdlRenderer(SDL_Window* mWindow, SDL_Renderer* mRenderer);

private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};
