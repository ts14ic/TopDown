//
// Created by ts14ic on 12/2/17.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "RenderBase.h"
#include "sdlwrap.h"
#include "Texture.h"
#include "Sound.h"

RenderBase::RenderBase(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
    init();
    load_media();
}

RenderBase::RenderBase() : RenderBase(800, 600) {}

void RenderBase::init() {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(initFlags)) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mWindow.reset(SDL_CreateWindow(
            "TopDown - Reborn",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            mScreenWidth, mScreenHeight,
            SDL_WINDOW_SHOWN
    ));
    if(!mWindow) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mRenderer.reset(SDL_CreateRenderer(
            mWindow.get(), -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC
    ));
    if(!mRenderer) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSDLInitException{IMG_GetError()};
    }

    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSDLInitException{Mix_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(mRenderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

RenderBase::~RenderBase() {
    SDL_Quit();
}

SDL_Renderer* RenderBase::getRenderer() {
    return mRenderer.get();
}

void RenderBase::load_texture(const char* name, const char* filename) {
    textures(name).load(*this, filename);
}

void RenderBase::load_media() {
    load_texture("player_pistol", "gfx/Player/pistol.png");
    load_texture("player_shotgun", "gfx/Player/shotgun.png");
    load_texture("player_uzi", "gfx/Player/uzi.png");
    load_texture("crosshair", "gfx/crosshair.png");
    load_texture("reload", "gfx/reload.png");
    load_texture("bullet", "gfx/bullet.png");
    load_texture("zombie", "gfx/Zombie/idle.png");
    load_texture("zombie_attack0", "gfx/Zombie/Attack/1.png");
    load_texture("zombie_attack1", "gfx/Zombie/Attack/2.png");
    load_texture("zombie_attack2", "gfx/Zombie/Attack/3.png");
    load_texture("zombie_attack3", "gfx/Zombie/Attack/4.png");
    load_texture("zombie_attack4", "gfx/Zombie/Attack/5.png");
    load_texture("zombie_attack5", "gfx/Zombie/Attack/6.png");
    load_texture("zombie_death0", "gfx/Zombie/Death/1.png");
    load_texture("zombie_death1", "gfx/Zombie/Death/2.png");
    load_texture("zombie_death2", "gfx/Zombie/Death/3.png");
    load_texture("zombie_death3", "gfx/Zombie/Death/4.png");
    load_texture("zombie_death4", "gfx/Zombie/Death/5.png");
    load_texture("zombie_death5", "gfx/Zombie/Death/6.png");
    load_texture("zombie_death6", "gfx/Zombie/Death/7.png");
    load_texture("zombie_death7", "gfx/Zombie/Death/8.png");
    load_texture("wolf_move0", "gfx/Werewolf/Alive/1.png");
    load_texture("wolf_move1", "gfx/Werewolf/Alive/2.png");
    load_texture("wolf_move2", "gfx/Werewolf/Alive/3.png");
    load_texture("wolf_move3", "gfx/Werewolf/Alive/4.png");
    load_texture("wolf_move4", "gfx/Werewolf/Alive/5.png");
    load_texture("wolf_move5", "gfx/Werewolf/Alive/6.png");
    load_texture("wolf_attack0", "gfx/Werewolf/Attack/1.png");
    load_texture("wolf_attack1", "gfx/Werewolf/Attack/2.png");
    load_texture("wolf_attack2", "gfx/Werewolf/Attack/3.png");
    load_texture("wolf_attack3", "gfx/Werewolf/Attack/4.png");
    load_texture("wolf_attack4", "gfx/Werewolf/Attack/5.png");
    load_texture("wolf_attack5", "gfx/Werewolf/Attack/6.png");
    load_texture("wolf_attack6", "gfx/Werewolf/Attack/7.png");
    load_texture("wolf_attack7", "gfx/Werewolf/Attack/8.png");
    load_texture("wolf_teleport0", "gfx/Werewolf/Teleportation/1.png");
    load_texture("wolf_teleport1", "gfx/Werewolf/Teleportation/2.png");
    load_texture("wolf_teleport2", "gfx/Werewolf/Teleportation/3.png");

    sounds("pistol_shot").load("sfx/pistol_shot.mp3");
    sounds("shotgun_shot").load("sfx/shotgun_shot.mp3");
    sounds("uzi_shot1").load("sfx/uzi_shot1.mp3");
    sounds("uzi_shot2").load("sfx/uzi_shot2.mp3");
    sounds("zombie_attack").load("sfx/zombie_attack.mp3");
    sounds("wolf_attack").load("sfx/wolf_attack.mp3");
    sounds("wolf_teleport").load("sfx/wolf_teleport.mp3");

    music("weather").load("sfx/weather.mp3");
}
