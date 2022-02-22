#include <iostream>

#include "SoundManager.h"
#include "Utils.h"

SoundManager* SoundManager::s_pInstance = nullptr;

SoundManager* SoundManager::Instance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new SoundManager();
        return s_pInstance;
    }
    return s_pInstance;
}

bool SoundManager::load(const std::string& fileName, const std::string& id, const sound_type type)
{
    if(type == sound_type::SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(utils::deepSearch(fileName).c_str());
        if(pMusic == nullptr)
        {
            std::cerr << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            _ASSERT(false);
            return false;
        }
        m_music[id] = pMusic;
        return true;
    }

    if(type == sound_type::SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(utils::deepSearch(fileName).c_str());
        if(pChunk == nullptr)
        {
            std::cerr << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            _ASSERT(false);
            return false;
        }
        m_sfxs[id] = pChunk;
        return true;
    }

    return false;
}

void SoundManager::playSound(const std::string& id, const int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playMusic(const std::string& id, const int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}
