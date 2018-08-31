//
// Created by ts14ic on 12/13/17.
//

#include "SdlResources.h"
#include <SDL_image.h>
#include <SDL.h>

SdlResources::FailedSdlInitException::FailedSdlInitException(const char* message)
        : runtime_error(message) {}

SdlResources::FailedSdlMixerInitException::FailedSdlMixerInitException(const char* message)
        : runtime_error(message) {}

SdlResources::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {}

SdlResources::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

SdlResources::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}

SdlResources::SdlResources(int width, int height) {
    initGraphicsSystem(width, height);
    initAudioSystem();
}

SdlResources::~SdlResources() {
    mNameToTexture.clear();
    mNameToMusic.clear();
    mNameToSound.clear();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Texture& SdlResources::getTexture(std::string const& name) {
    return mNameToTexture[name];
}

Music& SdlResources::getMusic(std::string const& name) {
    return mNameToMusic[name];
}

Sound& SdlResources::getSound(std::string const& name) {
    return mNameToSound[name];
}

void SdlResources::loadTexture(std::string const& name, const char* path) {
    mNameToTexture.insert(std::make_pair(name, std::move(loadTexture(path))));
}

SdlTexture SdlResources::loadTexture(const char* path) {
    struct SDLSurfaceDeleter {
        void operator()(SDL_Surface* surf) {
            SDL_FreeSurface(surf);
        }
    };

    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> buf{IMG_Load(path)};
    if(!buf) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    std::unique_ptr<SDL_Texture, SdlTexture::TextureDeleter> newTex{
            SDL_CreateTextureFromSurface(mRenderer.get(), buf.get())
    };
    if(!newTex) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SdlTexture tex{std::move(newTex), buf->w, buf->h};
    SDL_Log("SdlTexture loaded: %s.\n", path);

    return tex;
}

void SdlResources::loadSound(std::string const& name, const char* path) {
    mNameToSound.insert(std::make_pair(name, std::move(loadSound(path))));
}

void SdlResources::loadMusic(const std::string& name, const char* path) {
    mNameToMusic.insert(std::make_pair(name, std::move(loadMusic(path))));
}

SdlSound SdlResources::loadSound(const char* path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> newSound{Mix_LoadWAV(path)};
    if(!newSound) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(newSound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
}

SdlMusic SdlResources::loadMusic(const char* path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> newMusic{Mix_LoadMUS(path)};
    if(!newMusic) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(newMusic)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}

void SdlResources::initGraphicsSystem(int screenWidth, int screenHeight) {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(initFlags)) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    mWindow.reset(
            SDL_CreateWindow(
                    "TopDown - Reborn",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    screenWidth, screenHeight,
                    SDL_WINDOW_SHOWN
            )
    );
    if(!mWindow) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    mRenderer.reset(
            SDL_CreateRenderer(
                    mWindow.get(), -1,
                    SDL_RENDERER_ACCELERATED |
                    SDL_RENDERER_PRESENTVSYNC
            )
    );
    if(!mRenderer) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSdlInitException{IMG_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(mRenderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

void SdlResources::initAudioSystem() {
    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}

SDL_Window* SdlResources::getWindow() const {
    return mWindow.get();
}

SDL_Renderer* SdlResources::getRenderer() const {
    return mRenderer.get();
}

const Clock& SdlResources::getClock() {
    return *this;
}

void SdlResources::SdlDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlResources::SdlDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
