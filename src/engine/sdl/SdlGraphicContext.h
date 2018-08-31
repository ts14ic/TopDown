#pragma once

#include "engine/graphic/GraphicContext.h"
#include "engine/resources/Texture.h"
#include "SdlTexture.h"

class SdlGraphicContext : public GraphicContext {
public:
    SdlGraphicContext(SDL_Window* window, SDL_Renderer* renderer);

    void refreshScreen() override;

    void clearScreen() override;

    void renderBox(const Box& box, const Color& color) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    int getScreenWidth() override;

    int getScreenHeight() override;

private:
    int mScreenWidth;
    int mScreenHeight;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};
