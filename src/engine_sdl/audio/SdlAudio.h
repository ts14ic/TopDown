#pragma once

#include "SdlSound.h"
#include "SdlMusic.h"
#include <engine/audio/Audio.h>
#include <stdexcept>
#include <unordered_map>

class SdlAudio : public Audio {
public:
    SdlAudio();

    ~SdlAudio() override;

    void init();

    void deinit();

    void play_sound(const std::string& name) override;

    void load_sound(const std::string& name, const char* path) override;

    void play_music(const std::string& name) override;

    void load_music(const std::string& name, const char* path) override;

private:
    SdlSound load_sound(const char* path);

    void play_sound(const SdlSound& sound);

    SdlMusic load_music(const char* path);

    void play_music(const SdlMusic& music);

    std::unordered_map<std::string, SdlSound> _name_to_sound;
    std::unordered_map<std::string, SdlMusic> _name_to_music;
};
