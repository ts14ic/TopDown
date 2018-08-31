#include "SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>

SdlEngine::FailedSdlInitException::FailedSdlInitException(const char* message)
        : runtime_error(message) {}

SdlEngine::FailedSdlMixerInitException::FailedSdlMixerInitException(const char* message)
        : runtime_error(message) {}

SdlEngine::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {}

SdlEngine::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

SdlEngine::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}

SdlEngine::SdlEngine(int width, int height) {
    init_graphic_system(width, height);
    init_audio_system();
}

SdlEngine::~SdlEngine() {
    _name_to_texture.clear();
    _name_to_music.clear();
    _name_to_sound.clear();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Texture& SdlEngine::get_texture(std::string const &name) {
    return _name_to_texture[name];
}

Music& SdlEngine::get_music(std::string const &name) {
    return _name_to_music[name];
}

Sound& SdlEngine::get_sound(std::string const &name) {
    return _name_to_sound[name];
}

void SdlEngine::load_texture(std::string const &name, const char *path) {
    _name_to_texture.insert(std::make_pair(name, load_texture(path)));
}

SdlTexture SdlEngine::load_texture(const char *path) {
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

void SdlEngine::load_sound(std::string const &name, const char *path) {
    _name_to_sound.insert(std::make_pair(name, load_sound(path)));
}

void SdlEngine::load_music(const std::string &name, const char *path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlSound SdlEngine::load_sound(const char *path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> new_sound{Mix_LoadWAV(path)};
    if(!new_sound) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(new_sound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
}

SdlMusic SdlEngine::load_music(const char *path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> new_music{Mix_LoadMUS(path)};
    if(!new_music) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(new_music)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}

void SdlEngine::init_graphic_system(int screenWidth, int screenHeight) {
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

void SdlEngine::init_audio_system() {
    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}

SDL_Window* SdlEngine::get_window() const {
    return _window.get();
}

SDL_Renderer* SdlEngine::get_renderer() const {
    return _renderer.get();
}

const Clock& SdlEngine::get_clock() {
    return sdlClock;
}

void SdlEngine::SdlDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlEngine::SdlDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
