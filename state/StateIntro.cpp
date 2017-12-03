#include "GameState.h"
#include "../engine/Engine.h"
#include "StateIntro.h"

StateIntro::StateIntro(Engine& engine)
        : _background(engine.getRenderSystem(), "assets/gfx/intro_bg.png") {}

void StateIntro::handle_events(Engine& engine) {
    auto& input = engine.getInputSystem();

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
    _background.render(engine.getRenderSystem(), 0, 0);

    SDL_RenderPresent(engine.getRenderSystem().getRenderer());
}