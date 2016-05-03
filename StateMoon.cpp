#include "GameState.h"
#include "sdlwrap.h"
#include <SDL_events.h>
#include <SDL_render.h>

StateMoon::StateMoon()
: _texBackground("gfx/test_bg.png")
{
}

void StateMoon::handle_events() {
    while(SDL_PollEvent(&gameEvent())) {
        switch(gameEvent().type) {
            case SDL_QUIT:
            prepare_state(GState::exit);
            break;
            
            default:;
        }
    }
}

void StateMoon::handle_logic() {
    
}

void StateMoon::handle_render() {
    SDL_RenderClear(renderer());
    
    _texBackground.render(0, 0);
    
    SDL_RenderPresent(renderer());
}
