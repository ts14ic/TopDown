#include "GameState.h"
#include "sdlwrap.h"
#include <SDL_events.h>
#include <SDL_render.h>

StateIntro::StateIntro()
: _background("gfx/intro_bg.png") {}

void StateIntro::handle_events() {
    while(SDL_PollEvent(&gameEvent())) {
        switch(gameEvent().type) {
            case SDL_QUIT:
            prepare_state(GState::exit);
            break;
            
            case SDL_KEYDOWN:
            switch(gameEvent().key.keysym.sym) {
                case SDLK_q:
                prepare_state(GState::exit);
                break;
                break;
            }
            break;
            
            default:;
        }
    }
}

void StateIntro::handle_logic() {}

void StateIntro::handle_render() {
    _background.render(0, 0);
    
    SDL_RenderPresent(renderer());
}
