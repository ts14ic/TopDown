#include "StateIntro.h"
#include "../engine/Engine.h"
#include "../resources/Resources.h"
#include "../resources/Texture.h"
#include "../engine/InputContext.h"
#include "../engine/GraphicContext.h"
#include <SDL_render.h>
#include <SDL_events.h>

StateIntro::StateIntro(Engine& engine)
        : mBackgroundTexId{"intro_background"} {

    engine.getResources().loadTexture(mBackgroundTexId, "assets/gfx/intro_bg.png");
}

void StateIntro::handle_events(Engine& engine) {
    auto& input = engine.getInputContext();

    while(SDL_PollEvent(&input.getInputEvent())) {
        switch(input.getInputEvent().type) {
            case SDL_QUIT: {
                engine.requestStateChange(GState::exit);
                break;
            }

            case SDL_KEYDOWN: {
                switch(input.getInputEvent().key.keysym.sym) {
                    case SDLK_q:
                        engine.requestStateChange(GState::exit);
                        break;

                    case SDLK_RETURN:
                    case SDLK_ESCAPE:
                        engine.requestStateChange(GState::moon);
                        break;

                    default:
                        break;
                }
                break;
            }

            default:;
        }
    }
}

void StateIntro::handle_logic(Engine& engine) {}

void StateIntro::handle_render(Engine& engine) {
    auto& render = engine.getRenderContext();

    Texture& background = engine.getResources().getTexture(mBackgroundTexId);
    render.render(background, 0, 0);

    render.refreshScreen();
}
