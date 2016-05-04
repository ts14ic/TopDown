#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <string>

struct FailedToLoadSoundException {};
struct FailedToLoadMusicException {};

/* forward declarations begin */
struct Mix_Chunk;
struct _Mix_Music;
/* forward declarations end */

class Sound {
public:
    Sound();
    Sound(char const* path);
    ~Sound();
    
    Sound(Sound const&) = delete;
    Sound(Sound&&) = delete;
    
    void load(char const* path);
    
    void play() const;
private:
    Mix_Chunk* _chunk = nullptr;
};

Sound& sounds(std::string const& name);

class Music {
public:
    Music();
    Music(char const* path);
    ~Music();
    
    Music(Music const&) = delete;
    Music(Music&&) = delete;
    
    void load(char const* path);
    void play() const;
private:
    _Mix_Music* _mus;
};

Music& music(std::string const& name);

#endif
