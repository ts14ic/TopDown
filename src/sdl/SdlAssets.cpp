//
// Created by ts14ic on 12/13/17.
//

#include "SdlAssets.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

SdlAssets::FailedSdlInitException::FailedSdlInitException(const char* message)
        : runtime_error(message) {}


SdlAssets::FailedSdlMixerInitException::FailedSdlMixerInitException(const char* message)
        : runtime_error(message) {}

SdlAssets::~SdlAssets() {
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SdlAssets::setRenderContext(GraphicContext& graphicContext) {
    mGraphicContext = dynamic_cast<SdlGraphicContext*>(&graphicContext);
    if(mGraphicContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlGraphicContext"};
    }
    initGraphicsSystem();
}

void SdlAssets::setAudioContext(AudioContext& audioContext) {
    mAudioContext = dynamic_cast<SdlAudioContext*>(&audioContext);
    if(mAudioContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlAudioContext"};
    }
    initAudioSystem();
}

Texture& SdlAssets::getTexture(std::string const& name) {
    return mNameToTexture[name];
}

Music& SdlAssets::getMusic(std::string const& name) {
    return mNameToMusic[name];
}

Sound& SdlAssets::getSound(std::string const& name) {
    return mNameToSound[name];
}

void SdlAssets::loadTexture(std::string const& name, const char* path) {
    mNameToTexture.insert(std::make_pair(name, std::move(mGraphicContext->loadTexture(path))));
}

void SdlAssets::loadSound(std::string const& name, const char* path) {
    mNameToSound.insert(std::make_pair(name, std::move(mAudioContext->loadSound(path))));
}

void SdlAssets::loadMusic(const std::string& name, const char* path) {
    mNameToMusic.insert(std::make_pair(name, std::move(mAudioContext->loadMusic(path))));
}

void SdlAssets::initGraphicsSystem() {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(initFlags)) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    std::unique_ptr<SDL_Window, SdlGraphicContext::SdlDeleter> window{
            SDL_CreateWindow(
                    "TopDown - Reborn",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    mGraphicContext->getScreenWidth(),
                    mGraphicContext->getScreenHeight(),
                    SDL_WINDOW_SHOWN
            )
    };
    if(!window) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    std::unique_ptr<SDL_Renderer, SdlGraphicContext::SdlDeleter> renderer{
            SDL_CreateRenderer(
                    window.get(), -1,
                    SDL_RENDERER_ACCELERATED |
                    SDL_RENDERER_PRESENTVSYNC
            )
    };
    if(!renderer) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSdlInitException{IMG_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(renderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(renderer.get());
    SDL_RenderPresent(renderer.get());

    mGraphicContext->setSdlRenderer(std::move(window), std::move(renderer));
}

void SdlAssets::initAudioSystem() {
    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}
