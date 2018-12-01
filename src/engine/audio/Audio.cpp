#include "Audio.h"

Audio::~Audio() = default;

Audio::FailedAudioInitException::FailedAudioInitException(cstring message)
        : runtime_error(message) {}

Audio::FailedToLoadSoundException::FailedToLoadSoundException(cstring message)
        : runtime_error(message) {}

Audio::FailedToLoadMusicException::FailedToLoadMusicException(cstring message)
        : runtime_error(message) {}
