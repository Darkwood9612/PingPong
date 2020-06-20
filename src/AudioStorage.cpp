#include "AudioStorage.h"
#include <stdexcept>

AudioStorage::AudioStorage(int frequency, Uint16 format, int channels,
                           int chunksize)
{
  if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0) {
    std::string err = Mix_GetError();
    throw std::runtime_error("Fatal Mix_OpenAudio error: " + err);
  }
}

void AudioStorage::LoadSoundEffect(const std::string name, const char* path)
{
  if (auto soundEffect = Mix_LoadWAV(path)) {

    auto findResult = this->storageSoundEffect.find(name);

    findResult == this->storageSoundEffect.end()
      ? this->storageSoundEffect[name] = soundEffect
      : throw std::runtime_error("LoadMID error: SoundEffect already exists");

    return;
  }

  throw std::runtime_error("LoadMID error: SoundEffect == nullptr");
}

void AudioStorage::LoadMusic(const std::string name, const char* path)
{
  if (auto music = Mix_LoadMUS(path)) {

    auto findResult = this->storageMusic.find(name);

    findResult == this->storageMusic.end()
      ? this->storageMusic[name] = music
      : throw std::runtime_error("LoadMID error: music already exists");

    return;
  }

  throw std::runtime_error("LoadMID error: music == nullptr");
}

void AudioStorage::operator=(const AudioStorage& audioStorage)
{
  this->storageMusic = audioStorage.storageMusic;
  this->storageSoundEffect = audioStorage.storageSoundEffect;
}

void AudioStorage::FreeMusic(const std::string name)
{
  auto findResult = this->storageMusic.find(name);

  if (findResult != this->storageMusic.end()) {
    Mix_FreeMusic(findResult->second);
    this->storageMusic.erase(findResult);
  }
}

void AudioStorage::FreeAllMusic()
{
  for (auto& item : this->storageMusic)
    Mix_FreeMusic(item.second);

  this->storageMusic.clear();
}

void AudioStorage::FreeSoundEffect(const std::string name)
{
  auto findResult = this->storageSoundEffect.find(name);

  if (findResult != this->storageSoundEffect.end()) {
    Mix_FreeChunk(findResult->second);
    this->storageSoundEffect.erase(findResult);
  }
}

void AudioStorage::FreeAllSoundEffect()
{
  for (auto& item : this->storageSoundEffect)
    Mix_FreeChunk(item.second);

  this->storageSoundEffect.clear();
}

void AudioStorage::PlayMusic(const std::string name, int loops)
{
  auto music = storageMusic.find(name);

  if (music == storageMusic.end()) {
    throw std::runtime_error("PlayMusic error: music not found. name: " +
                             name);
  }

  if (Mix_FadeInMusic(music->second, loops, 0) == -1) {
    std::string err = Mix_GetError();
    throw std::runtime_error("Mix_PlayMusic: " + err);
  }
}

void AudioStorage::PlaySoundEffect(const std::string name, int loops)
{
  auto soundEffect = storageSoundEffect.find(name);

  if (soundEffect == storageSoundEffect.end()) {
    throw std::runtime_error("PlayMusic error: soundEffect not found. name: " +
                             name);
  }

  Mix_PlayChannel(-1, soundEffect->second, loops);
}
