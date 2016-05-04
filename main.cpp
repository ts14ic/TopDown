#include "sdlwrap.h"
#include "GameState.h"
#include "StopWatch.h"
#include <SDL_timer.h>

void load_media() {
    textures("player_pistol").load("gfx/Player/pistol.png");
    textures("bullet").load("gfx/bullet.png");
}

int main(int, char*[]) {
    if(!init_sdl()) {
        return -1;
    }
    
    load_media();
    
    currentStateID() = GState::intro;
    currentState().reset(new StateIntro);
    
    StopWatch fpsCapper;
    while(currentStateID() != GState::exit) {
        fpsCapper.start();
        
        currentState()->handle_events();
        currentState()->handle_logic();
        
        change_state();
        
        currentState()->handle_render();
        
        if(fpsCapper.get_ticks() < minSpf) {
            SDL_Delay(minSpf - fpsCapper.get_ticks());
        }
    }
    
    close_sdl();
}
