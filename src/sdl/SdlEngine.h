#pragma once

#include "engine/Engine.h"
#include "random/Mt19937Random.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include "SdlClock.h"
#include "SdlGraphic.h"
#include "SdlAudio.h"
#include "SdlInput.h"
#include <SDL_render.h>
#include <unordered_map>

class SdlEngine : public Engine {
public:
    SdlEngine(int screen_width, int screen_height);

    ~SdlEngine() override;

    Graphic& get_graphic() override;

    Audio& get_audio() override;

    Input& get_input() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    void load_texture(const std::string& name, const char* path) override;

    Texture& get_texture(const std::string& name) override;

    Sound& get_sound(const std::string& name) override;

    void load_sound(const std::string& name, const char* path) override;

    Music& get_music(const std::string& name) override;

    void load_music(const std::string& name, const char* path) override;

private:
    SdlSound load_sound(const char* path);

    SdlMusic load_music(const char* path);

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    std::unordered_map<std::string, SdlSound> _name_to_sound;
    std::unordered_map<std::string, SdlMusic> _name_to_music;

    Mt19937Random _random;
    SdlGraphic _graphic;
    SdlAudio _audio;
    SdlInput _input;
    SdlClock _clock;
};
