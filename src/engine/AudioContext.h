//
// Created by ts14ic on 12/13/17.
//
#pragma once

class Sound;

class Music;

class AudioContext {
public:
    virtual ~AudioContext();

    virtual void playSound(const Sound& sound) = 0;

    virtual void playMusic(const Music& music) = 0;
};
