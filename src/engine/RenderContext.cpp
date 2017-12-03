//
// Created by ts14ic on 12/2/17.
//
#include "RenderContext.h"
#include "../texture/Texture.h"
#include "../sound/Sound.h"
#include "../sound/Music.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

RenderContext::RenderContext(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
    init();
    load_media();
}

RenderContext::RenderContext() : RenderContext(800, 600) {}

void RenderContext::init() {
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

RenderContext::~RenderContext() {
    SDL_Quit();
}

SDL_Renderer* RenderContext::getRenderer() {
    return mRenderer.get();
}

void RenderContext::load_texture(const char* name, const char* filename) {
    textures(name).load(*this, filename);
}

int RenderContext::getScreenHeight() {
    return mScreenHeight;
}

int RenderContext::getScreenWidth() {
    return mScreenWidth;
}

// todo move this method to Engine
void RenderContext::load_media() {
    load_texture("player_pistol", "assets/gfx/Player/pistol.png");
    load_texture("player_shotgun", "assets/gfx/Player/shotgun.png");
    load_texture("player_uzi", "assets/gfx/Player/uzi.png");
    load_texture("crosshair", "assets/gfx/crosshair.png");
    load_texture("reload", "assets/gfx/reload.png");
    load_texture("bullet", "assets/gfx/bullet.png");
    load_texture("zombie", "assets/gfx/Zombie/idle.png");
    load_texture("zombie_attack0", "assets/gfx/Zombie/Attack/1.png");
    load_texture("zombie_attack1", "assets/gfx/Zombie/Attack/2.png");
    load_texture("zombie_attack2", "assets/gfx/Zombie/Attack/3.png");
    load_texture("zombie_attack3", "assets/gfx/Zombie/Attack/4.png");
    load_texture("zombie_attack4", "assets/gfx/Zombie/Attack/5.png");
    load_texture("zombie_attack5", "assets/gfx/Zombie/Attack/6.png");
    load_texture("zombie_death0", "assets/gfx/Zombie/Death/1.png");
    load_texture("zombie_death1", "assets/gfx/Zombie/Death/2.png");
    load_texture("zombie_death2", "assets/gfx/Zombie/Death/3.png");
    load_texture("zombie_death3", "assets/gfx/Zombie/Death/4.png");
    load_texture("zombie_death4", "assets/gfx/Zombie/Death/5.png");
    load_texture("zombie_death5", "assets/gfx/Zombie/Death/6.png");
    load_texture("zombie_death6", "assets/gfx/Zombie/Death/7.png");
    load_texture("zombie_death7", "assets/gfx/Zombie/Death/8.png");
    load_texture("wolf_move0", "assets/gfx/Werewolf/Alive/1.png");
    load_texture("wolf_move1", "assets/gfx/Werewolf/Alive/2.png");
    load_texture("wolf_move2", "assets/gfx/Werewolf/Alive/3.png");
    load_texture("wolf_move3", "assets/gfx/Werewolf/Alive/4.png");
    load_texture("wolf_move4", "assets/gfx/Werewolf/Alive/5.png");
    load_texture("wolf_move5", "assets/gfx/Werewolf/Alive/6.png");
    load_texture("wolf_attack0", "assets/gfx/Werewolf/Attack/1.png");
    load_texture("wolf_attack1", "assets/gfx/Werewolf/Attack/2.png");
    load_texture("wolf_attack2", "assets/gfx/Werewolf/Attack/3.png");
    load_texture("wolf_attack3", "assets/gfx/Werewolf/Attack/4.png");
    load_texture("wolf_attack4", "assets/gfx/Werewolf/Attack/5.png");
    load_texture("wolf_attack5", "assets/gfx/Werewolf/Attack/6.png");
    load_texture("wolf_attack6", "assets/gfx/Werewolf/Attack/7.png");
    load_texture("wolf_attack7", "assets/gfx/Werewolf/Attack/8.png");
    load_texture("wolf_teleport0", "assets/gfx/Werewolf/Teleportation/1.png");
    load_texture("wolf_teleport1", "assets/gfx/Werewolf/Teleportation/2.png");
    load_texture("wolf_teleport2", "assets/gfx/Werewolf/Teleportation/3.png");

    sounds("pistol_shot").load("assets/sfx/pistol_shot.mp3");
    sounds("shotgun_shot").load("assets/sfx/shotgun_shot.mp3");
    sounds("uzi_shot1").load("assets/sfx/uzi_shot1.mp3");
    sounds("uzi_shot2").load("assets/sfx/uzi_shot2.mp3");
    sounds("zombie_attack").load("assets/sfx/zombie_attack.mp3");
    sounds("wolf_attack").load("assets/sfx/wolf_attack.mp3");
    sounds("wolf_teleport").load("assets/sfx/wolf_teleport.mp3");

    music("weather").load("assets/sfx/weather.mp3");
}

void RenderContext::SDLDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void RenderContext::SDLDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
