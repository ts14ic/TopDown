#pragma once

#include "engine/Engine.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include "SdlClock.h"
#include <SDL_render.h>
#include <unordered_map>

class SdlEngine : public Engine {
public:
    SdlEngine(int width, int height);

    ~SdlEngine() override;

    Texture& get_texture(const std::string &name) override;

    Sound& get_sound(const std::string &name) override;

    Music& get_music(const std::string &name) override;

    const Clock& get_clock() override;

    void load_texture(const std::string &name, const char *path) override;

    void load_sound(const std::string &name, const char *path) override;

    void load_music(const std::string &name, const char *path) override;

    SDL_Window* get_window() const;

    SDL_Renderer* get_renderer() const;

    struct FailedSdlInitException : public std::runtime_error {
        explicit FailedSdlInitException(const char* message);
    };

    struct FailedSdlMixerInitException : public std::runtime_error {
        explicit FailedSdlMixerInitException(const char* message);
    };

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    void init_graphic_system(int width, int height);

    void init_audio_system();

    SdlTexture load_texture(const char *path);

    struct SdlDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    SdlSound load_sound(const char *path);

    SdlMusic load_music(const char *path);

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    std::unique_ptr<SDL_Window, SdlDeleter> _window;
    std::unique_ptr<SDL_Renderer, SdlDeleter> _renderer;
    std::unordered_map<std::string, SdlSound> _name_to_sound;
    std::unordered_map<std::string, SdlTexture> _name_to_texture;
    std::unordered_map<std::string, SdlMusic> _name_to_music;
    SdlClock sdlClock;
};
