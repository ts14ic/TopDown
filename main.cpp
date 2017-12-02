#include "sdlwrap.h"
#include "GameState.h"
#include "Sound.h"
#include "EngineBase.h"
#include <SDL_timer.h>
#include <iostream>

void load_media() {
    textures("player_pistol").load("gfx/Player/pistol.png");
    sounds("pistol_shot").load("sfx/pistol_shot.mp3");
    
    textures("player_shotgun").load("gfx/Player/shotgun.png");
    sounds("shotgun_shot").load("sfx/shotgun_shot.mp3");
    
    textures("player_uzi").load("gfx/Player/uzi.png");
    sounds("uzi_shot1").load("sfx/uzi_shot1.mp3");
    sounds("uzi_shot2").load("sfx/uzi_shot2.mp3");
    
    textures("crosshair").     load("gfx/crosshair.png");
    textures("reload").        load("gfx/reload.png");
    
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
    
    textures("wolf_move0").load("gfx/Werewolf/Alive/1.png");
    textures("wolf_move1").load("gfx/Werewolf/Alive/2.png");
    textures("wolf_move2").load("gfx/Werewolf/Alive/3.png");
    textures("wolf_move3").load("gfx/Werewolf/Alive/4.png");
    textures("wolf_move4").load("gfx/Werewolf/Alive/5.png");
    textures("wolf_move5").load("gfx/Werewolf/Alive/6.png");
    textures("wolf_attack0").load("gfx/Werewolf/Attack/1.png");
    textures("wolf_attack1").load("gfx/Werewolf/Attack/2.png");
    textures("wolf_attack2").load("gfx/Werewolf/Attack/3.png");
    textures("wolf_attack3").load("gfx/Werewolf/Attack/4.png");
    textures("wolf_attack4").load("gfx/Werewolf/Attack/5.png");
    textures("wolf_attack5").load("gfx/Werewolf/Attack/6.png");
    textures("wolf_attack6").load("gfx/Werewolf/Attack/7.png");
    textures("wolf_attack7").load("gfx/Werewolf/Attack/8.png");
    textures("wolf_teleport0").load("gfx/Werewolf/Teleportation/1.png");
    textures("wolf_teleport1").load("gfx/Werewolf/Teleportation/2.png");
    textures("wolf_teleport2").load("gfx/Werewolf/Teleportation/3.png");
    sounds("wolf_attack").  load("sfx/wolf_attack.mp3");
    sounds("wolf_teleport").load("sfx/wolf_teleport.mp3");
    
    music("weather").load("sfx/weather.mp3");
}

int main(int, char*[]) {
    EngineBase engine;
    load_media();
    
    currentStateID() = GState::intro;
    currentState()   = std::make_unique<StateIntro>();

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
}
