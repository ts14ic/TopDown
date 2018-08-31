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
    init_graphic_system(width, height);
    init_audio_system();
}

SdlResources::~SdlResources() {
    _name_to_texture.clear();
    _name_to_music.clear();
    _name_to_sound.clear();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Texture& SdlResources::get_texture(std::string const &name) {
    return _name_to_texture[name];
}

Music& SdlResources::get_music(std::string const &name) {
    return _name_to_music[name];
}

Sound& SdlResources::get_sound(std::string const &name) {
    return _name_to_sound[name];
}

void SdlResources::load_texture(std::string const &name, const char *path) {
    _name_to_texture.insert(std::make_pair(name, load_texture(path)));
}

SdlTexture SdlResources::load_texture(const char *path) {
    struct SDLSurfaceDeleter {
        void operator()(SDL_Surface* surf) {
            SDL_FreeSurface(surf);
        }
    };

    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> buf{IMG_Load(path)};
    if(!buf) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    std::unique_ptr<SDL_Texture, SdlTexture::TextureDeleter> new_texture{
            SDL_CreateTextureFromSurface(_renderer.get(), buf.get())
    };
    if(!new_texture) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SdlTexture tex{std::move(new_texture), buf->w, buf->h};
    SDL_Log("SdlTexture loaded: %s.\n", path);

    return tex;
}

void SdlResources::load_sound(std::string const &name, const char *path) {
    _name_to_sound.insert(std::make_pair(name, load_sound(path)));
}

void SdlResources::load_music(const std::string &name, const char *path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlSound SdlResources::load_sound(const char *path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> new_sound{Mix_LoadWAV(path)};
    if(!new_sound) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(new_sound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
}

SdlMusic SdlResources::load_music(const char *path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> new_music{Mix_LoadMUS(path)};
    if(!new_music) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(new_music)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}

void SdlResources::init_graphic_system(int screenWidth, int screenHeight) {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(initFlags)) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    _window.reset(
            SDL_CreateWindow(
                    "TopDown - Reborn",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    screenWidth, screenHeight,
                    SDL_WINDOW_SHOWN
            )
    );
    if(!_window) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    _renderer.reset(
            SDL_CreateRenderer(
                    _window.get(), -1,
                    SDL_RENDERER_ACCELERATED |
                    SDL_RENDERER_PRESENTVSYNC
            )
    );
    if(!_renderer) {
        throw FailedSdlInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSdlInitException{IMG_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(_renderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(_renderer.get());
    SDL_RenderPresent(_renderer.get());
}

void SdlResources::init_audio_system() {
    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}

SDL_Window* SdlResources::get_window() const {
    return _window.get();
}

SDL_Renderer* SdlResources::get_renderer() const {
    return _renderer.get();
}

const Clock& SdlResources::get_clock() {
    return *this;
}

void SdlResources::SdlDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlResources::SdlDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
