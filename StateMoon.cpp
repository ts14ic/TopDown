#include "GameState.h"
#include "sdlwrap.h"
#include <SDL_events.h>
#include <SDL_render.h>

StateMoon::StateMoon()
: _texBackground("gfx/test_bg.png"),
  _pl(screenWidth() / 2, screenHeight() / 2)
{
    
}

void StateMoon::handle_events() {
    while(SDL_PollEvent(&gameEvent())) {
        
        _pl.handle_events();
        
        switch(gameEvent().type) {
            case SDL_QUIT:
            prepare_state(GState::exit);
            break;
            
            default:;
        }
    }
}

void StateMoon::handle_logic() {
    _pl.handle_logic();
}

void StateMoon::handle_render() {
    SDL_RenderClear(renderer());
    
    _texBackground.render(0, 0);
    
    _pl.handle_render();
    
    SDL_RenderPresent(renderer());
}
