//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../resources/Resources.h"
#include "../resources/Music.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <unordered_map>

class SdlGraphicContext;

class SdlAudioContext;

struct SDL_Window;
struct SDL_Renderer;

// todo rename to resources, move resource loading and renderer here
class SdlResources : public Resources {
public:
    SdlResources(int width, int height);

    ~SdlResources() override;

    void setRenderContext(GraphicContext& graphicContext) override;

    void setAudioContext(AudioContext& audioContext) override;

    int getScreenWidth() override;

    int getScreenHeight() override;

    Texture& getTexture(const std::string& name) override;

    void loadTexture(const std::string& name, const char* path) override;

    Sound& getSound(const std::string& name) override;

    void loadSound(const std::string& name, const char* path) override;

    Music& getMusic(const std::string& name) override;

    void loadMusic(const std::string& name, const char* path) override;

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
    void initGraphicsSystem();

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
    int mScreenWidth;
    int mScreenHeight;

    std::unique_ptr<SDL_Window, SdlDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SdlDeleter> mRenderer;
    std::unordered_map<std::string, SdlSound> mNameToSound;
    std::unordered_map<std::string, SdlTexture> mNameToTexture;
    std::unordered_map<std::string, SdlMusic> mNameToMusic;
};
