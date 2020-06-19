#include "AudioStorage.h"
#include <stdexcept>

AudioStorage::AudioStorage(int frequency, Uint16 format, int channels, int chunksize)
{
    if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0) {
        std::string err = Mix_GetError();
        throw std::runtime_error("Fatal Mix_OpenAudio error: " + err);
    }
}

void AudioStorage::LoadMID(const std::string name, const char* path)
{
    if (auto music = Mix_LoadMUS(path)) {

        auto findResult = this->storage.find(name);

        findResult == this->storage.end()
            ? this->storage[name] = music
            : throw std::runtime_error("LoadMID error: name already exists");

        return;
    }

    throw std::runtime_error("LoadMID error: music == nullptr");
}

void AudioStorage::operator=(const AudioStorage& audioStorage)
{
    this->storage = audioStorage.storage;
}

void AudioStorage::FreeMusic(const std::string name)
{
    auto findResult = this->storage.find(name);

    if (findResult != this->storage.end()) {
        Mix_FreeMusic(findResult->second);
        this->storage.erase(findResult);
    }
}

void AudioStorage::FreeAllMusic()
{
    for (auto& item : this->storage)
        Mix_FreeMusic(item.second);

    this->storage.clear();
}

void AudioStorage::PlayMusic(const std::string name, int loops)
{
    auto music = storage.find(name);

    if (music == storage.end()) {
        throw std::runtime_error("PlayMusic error: music not found. name: " + name);
    }

    if (Mix_FadeInMusic(music->second, loops, 10) == -1) {
        std::string err = Mix_GetError();
        throw std::runtime_error("Mix_PlayMusic: " + err);
    }
}