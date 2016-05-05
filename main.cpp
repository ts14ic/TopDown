#include "sdlwrap.h"
#include "GameState.h"
#include "StopWatch.h"
#include "Sound.h"
#include <SDL_timer.h>

void load_media() {
    textures("player_pistol").load("gfx/Player/pistol.png");
    sounds("pistol_shot").load("sfx/pistol_shot.mp3");
    
    textures("player_shotgun").load("gfx/Player/shotgun.png");
    sounds("shotgun_shot").load("sfx/shotgun_shot.mp3");
    
    textures("bullet").load("gfx/bullet.png");
    
    textures("zombie").    load("gfx/Zombie/idle.png");
    textures("zombie_attack0").load("gfx/Zombie/Attack/1.png");
    textures("zombie_attack1").load("gfx/Zombie/Attack/2.png");
    textures("zombie_attack2").load("gfx/Zombie/Attack/3.png");
    textures("zombie_attack3").load("gfx/Zombie/Attack/4.png");
    textures("zombie_attack4").load("gfx/Zombie/Attack/5.png");
    textures("zombie_attack5").load("gfx/Zombie/Attack/6.png");
    textures("zombie_death0").load("gfx/Zombie/Death/1.png");    
    textures("zombie_death1").load("gfx/Zombie/Death/2.png");    
    textures("zombie_death2").load("gfx/Zombie/Death/3.png");    
    textures("zombie_death3").load("gfx/Zombie/Death/4.png");    
    textures("zombie_death4").load("gfx/Zombie/Death/5.png");    
    textures("zombie_death5").load("gfx/Zombie/Death/6.png");    
    textures("zombie_death6").load("gfx/Zombie/Death/7.png");    
    textures("zombie_death7").load("gfx/Zombie/Death/8.png");  
    sounds("zombie_attack").load("sfx/zombie_attack.mp3");
    
    music("weather").load("sfx/weather.mp3");
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
