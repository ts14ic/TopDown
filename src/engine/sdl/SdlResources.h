#pragma once

#include "engine/resources/Resources.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include "SdlClock.h"
#include <SDL_render.h>
#include <unordered_map>

class SdlResources : public Resources, private SdlClock {
public:
    SdlResources(int width, int height);

    ~SdlResources() override;

    Texture& getTexture(const std::string& name) override;

    Sound& getSound(const std::string& name) override;

    Music& getMusic(const std::string& name) override;

    const Clock& getClock() override;

    void loadTexture(const std::string& name, const char* path) override;

    void loadSound(const std::string& name, const char* path) override;

    void loadMusic(const std::string& name, const char* path) override;

    SDL_Window* getWindow() const;

    SDL_Renderer* getRenderer() const;

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
    void initGraphicsSystem(int width, int height);

    void initAudioSystem();

    SdlTexture loadTexture(const char* path);

    struct SdlDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    SdlSound loadSound(const char* path);

    SdlMusic loadMusic(const char* path);

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    std::unique_ptr<SDL_Window, SdlDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SdlDeleter> mRenderer;
    std::unordered_map<std::string, SdlSound> mNameToSound;
    std::unordered_map<std::string, SdlTexture> mNameToTexture;
    std::unordered_map<std::string, SdlMusic> mNameToMusic;
};
