//
// Created by ts14ic on 12/2/17.
//

#include "DefaultEngine.h"
#include "../state/StateIntro.h"
#include "../state/StateMoon.h"
#include "../sound/Sound.h"
#include "../sound/Music.h"
#include <SDL_timer.h>

constexpr int MS_ONE_SECOND = 1000;
constexpr int FRAMES_PER_SECOND = 60;
constexpr int MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

DefaultEngine::DefaultEngine(
        std::unique_ptr<Assets> assets,
        std::unique_ptr<RenderContext> renderContext,
        std::unique_ptr<InputContext> inputContext,
        std::unique_ptr<Random> random)
        : mAssets(std::move(assets)),
          mRenderContext{std::move(renderContext)},
          mInputContext{std::move(inputContext)},
          mRandom{std::move(random)} {

    loadMedia();
}

void DefaultEngine::runLoop() {
    mCurrentState = std::make_unique<StateIntro>(*this);

    while(mCurrentStateId != GState::exit) {
        mFpsWatch.restart();

        mCurrentState->handle_events(*this);
        mCurrentState->handle_logic(*this);

        changeState();

        mCurrentState->handle_render(*this);

        if(mFpsWatch.getTicks() < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - mFpsWatch.getTicks());
        }
    }
}

void DefaultEngine::changeState() {
    if(mNextStateId != GState::null) {
        if(mNextStateId != GState::exit) {
            mCurrentState.reset(nullptr);
        }

        switch(mNextStateId) {
            case GState::intro:
                mCurrentState = std::make_unique<StateIntro>(*this);
                break;

            case GState::moon:
                mCurrentState = std::make_unique<StateMoon>(*this);
                break;

            default:;
        }

        mCurrentStateId = mNextStateId;
        mNextStateId = GState::null;
    }
}

void DefaultEngine::requestStateChange(GState stateId) {
    if(mNextStateId != GState::exit) {
        mNextStateId = stateId;
    }
}

InputContext& DefaultEngine::getInputContext() {
    return *mInputContext;
}

RenderContext& DefaultEngine::getRenderContext() {
    return *mRenderContext;
}

Assets& DefaultEngine::getAssets() {
    return *mAssets;
}

Random& DefaultEngine::getRandom() {
    return *mRandom;
}

void DefaultEngine::loadTexture(const char* name, const char* filename) {
    mAssets->texture(name).load(getRenderContext(), filename);
}

void DefaultEngine::loadSound(const char* name, const char* filename) {
    mAssets->sound(name).load(filename);
}

void DefaultEngine::loadMusic(const char* name, const char* filename) {
    mAssets->music(name).load(filename);
}

// todo use abstract asset classes
// todo fetch resource maps from a file
void DefaultEngine::loadMedia() {
    loadTexture("player", "assets/gfx/Player/hands.png");
    loadTexture("player_hands", "assets/gfx/Player/hands.png");
    loadTexture("player_aura", "assets/gfx/Player/aura.png");
    loadTexture("player_pistol", "assets/gfx/Player/pistol.png");
    loadTexture("player_shotgun", "assets/gfx/Player/shotgun.png");
    loadTexture("player_uzi", "assets/gfx/Player/uzi.png");
    loadTexture("crosshair", "assets/gfx/crosshair.png");
    loadTexture("reload", "assets/gfx/reload.png");
    loadTexture("bullet", "assets/gfx/bullet.png");
    loadTexture("zombie", "assets/gfx/Zombie/idle.png");
    loadTexture("zombie_attack0", "assets/gfx/Zombie/Attack/1.png");
    loadTexture("zombie_attack1", "assets/gfx/Zombie/Attack/2.png");
    loadTexture("zombie_attack2", "assets/gfx/Zombie/Attack/3.png");
    loadTexture("zombie_attack3", "assets/gfx/Zombie/Attack/4.png");
    loadTexture("zombie_attack4", "assets/gfx/Zombie/Attack/5.png");
    loadTexture("zombie_attack5", "assets/gfx/Zombie/Attack/6.png");
    loadTexture("zombie_death0", "assets/gfx/Zombie/Death/1.png");
    loadTexture("zombie_death1", "assets/gfx/Zombie/Death/2.png");
    loadTexture("zombie_death2", "assets/gfx/Zombie/Death/3.png");
    loadTexture("zombie_death3", "assets/gfx/Zombie/Death/4.png");
    loadTexture("zombie_death4", "assets/gfx/Zombie/Death/5.png");
    loadTexture("zombie_death5", "assets/gfx/Zombie/Death/6.png");
    loadTexture("zombie_death6", "assets/gfx/Zombie/Death/7.png");
    loadTexture("zombie_death7", "assets/gfx/Zombie/Death/8.png");
    loadTexture("wolf_move0", "assets/gfx/Werewolf/Alive/1.png");
    loadTexture("wolf_move1", "assets/gfx/Werewolf/Alive/2.png");
    loadTexture("wolf_move2", "assets/gfx/Werewolf/Alive/3.png");
    loadTexture("wolf_move3", "assets/gfx/Werewolf/Alive/4.png");
    loadTexture("wolf_move4", "assets/gfx/Werewolf/Alive/5.png");
    loadTexture("wolf_move5", "assets/gfx/Werewolf/Alive/6.png");
    loadTexture("wolf_attack0", "assets/gfx/Werewolf/Attack/1.png");
    loadTexture("wolf_attack1", "assets/gfx/Werewolf/Attack/2.png");
    loadTexture("wolf_attack2", "assets/gfx/Werewolf/Attack/3.png");
    loadTexture("wolf_attack3", "assets/gfx/Werewolf/Attack/4.png");
    loadTexture("wolf_attack4", "assets/gfx/Werewolf/Attack/5.png");
    loadTexture("wolf_attack5", "assets/gfx/Werewolf/Attack/6.png");
    loadTexture("wolf_attack6", "assets/gfx/Werewolf/Attack/7.png");
    loadTexture("wolf_attack7", "assets/gfx/Werewolf/Attack/8.png");
    loadTexture("wolf_teleport0", "assets/gfx/Werewolf/Teleportation/1.png");
    loadTexture("wolf_teleport1", "assets/gfx/Werewolf/Teleportation/2.png");
    loadTexture("wolf_teleport2", "assets/gfx/Werewolf/Teleportation/3.png");

    loadSound("pistol_shot", "assets/sfx/pistol_shot.mp3");
    loadSound("shotgun_shot", "assets/sfx/shotgun_shot.mp3");
    loadSound("uzi_shot1", "assets/sfx/uzi_shot1.mp3");
    loadSound("uzi_shot2", "assets/sfx/uzi_shot2.mp3");
    loadSound("zombie_attack", "assets/sfx/zombie_attack.mp3");
    loadSound("wolf_attack", "assets/sfx/wolf_attack.mp3");
    loadSound("wolf_teleport", "assets/sfx/wolf_teleport.mp3");

    loadMusic("weather", "assets/sfx/weather.mp3");
}