#include "GameState.h"
#include "sdlwrap.h"
#include "Engine.h"
#include <SDL_events.h>

StateIntro::StateIntro(RenderBase& engine)
        : _background(engine, "gfx/intro_bg.png") {}

void StateIntro::handle_events(Engine& engine) {
    while(SDL_PollEvent(&gameEvent())) {
        switch(gameEvent().type) {
            case SDL_QUIT: {
                engine.requestStateChange(GState::exit);
                break;
            }

            case SDL_KEYDOWN: {
                switch(gameEvent().key.keysym.sym) {
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

void StateIntro::handle_render(RenderBase& engine) {
    _background.render(engine, 0, 0);

    SDL_RenderPresent(engine.getRenderer());
}
