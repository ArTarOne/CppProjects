#pragma once
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

enum class sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    static SoundManager* Instance();
    /**
     * \brief Load a wave file or a music (.mod .s3m .it .xm) file
     * \param fileName [in] path to *.wav file
     * \param id [in] key value to later access
     * \param type [in] determine which one function should use to load sound: Mix_LoadMUS or Mix_LoadWAV
     * \return false in case of error
     */
    bool load(std::string fileName, std::string id, sound_type type);
    /**
     * \brief Play an audio chunk on a specific channel.
     * \param id [in] If the specified channel is -1, play on the first free channel
     * \param loop [in] If greater than zero, loop the sound that many times. If -1, loop infinitely (~65000 times).
     */
    void playSound(const std::string& id, int loop);
    /**
     * \brief Play an audio chunk on a specific channel.
     * \param id [in] If the specified channel is -1, play on the first free channel
     * \param loop [in] If greater than zero, loop the sound that many times. If -1, loop infinitely (~65000 times).
     */
    void playMusic(const std::string& id, int loop);

private:
    static SoundManager*              s_pInstance;
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager&)            = delete;
    SoundManager& operator=(const SoundManager&) = delete;
};

using TheSoundManager = SoundManager;
