//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../AudioContext.h"

class SdlSound;

class SdlMusic;

class SdlAudioContext : public AudioContext {
public:
    void playSound(const Sound& sound) override;

    void playMusic(const Music& music) override;
};
