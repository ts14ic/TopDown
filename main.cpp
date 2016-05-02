#include "sdlwrap.h"
#include "GameState.h"

int main(int, char*[]) {
    if(!init_sdl()) {
        return -1;
    }
    
    currentStateID() = GState::intro;
    currentState().reset(new StateIntro);
    
    while(currentStateID() != GState::exit) {
        currentState()->handle_events();
        currentState()->handle_logic();
        
        change_state();
        
        currentState()->handle_render();
    }
    
    close_sdl();
}
