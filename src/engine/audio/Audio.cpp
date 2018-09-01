#include "Audio.h"

Audio::~Audio() = default;

Audio::FailedAudioInitException::FailedAudioInitException(const char* message)
        : runtime_error(message) {}

Audio::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

Audio::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}
