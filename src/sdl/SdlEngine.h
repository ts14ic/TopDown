#pragma once

#include "engine/Engine.h"
#include "random/Mt19937Random.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include "SdlClock.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include "SdlInputContext.h"
#include <SDL_render.h>
#include <unordered_map>

class SdlEngine : public Engine {
public:
    SdlEngine(int screen_width, int screen_height);

    ~SdlEngine() override;

    GraphicContext& get_graphic_context() override;

    AudioContext& get_audio_context() override;

    InputContext& get_input_context() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    void load_texture(const std::string &name, const char *path) override;

    Texture& get_texture(const std::string &name) override;

    Sound& get_sound(const std::string &name) override;

    void load_sound(const std::string &name, const char *path) override;

    Music& get_music(const std::string &name) override;

    void load_music(const std::string &name, const char *path) override;

private:
    SdlTexture load_texture(const char *path);

    SdlSound load_sound(const char *path);

    SdlMusic load_music(const char *path);

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    std::unordered_map<std::string, SdlSound> _name_to_sound;
    std::unordered_map<std::string, SdlTexture> _name_to_texture;
    std::unordered_map<std::string, SdlMusic> _name_to_music;

    Mt19937Random _random;
    SdlGraphicContext _graphic;
    SdlAudioContext _audio;
    SdlInputContext _input;
    SdlClock _clock;
};
