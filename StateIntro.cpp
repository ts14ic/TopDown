#include "GameState.h"
#include "sdlwrap.h"
#include "EngineBase.h"
#include <SDL_events.h>

StateIntro::StateIntro(EngineBase& engine)
        : _background(engine, "gfx/intro_bg.png") {}

void StateIntro::handle_events() {
    while(SDL_PollEvent(&gameEvent())) {
        switch(gameEvent().type) {
            case SDL_QUIT: {
                prepare_state(GState::exit);
                break;
            }

            case SDL_KEYDOWN: {
                switch(gameEvent().key.keysym.sym) {
                    case SDLK_q:
                        prepare_state(GState::exit);
                        break;

                    case SDLK_RETURN:
                    case SDLK_ESCAPE:
                        prepare_state(GState::moon);
                        break;
                }
                break;
            }

            default:;
        }
    }
}

void StateIntro::handle_logic() {}

void StateIntro::handle_render(EngineBase& engine) {
    _background.render(engine, 0, 0);

    SDL_RenderPresent(engine.getRenderer());
}
