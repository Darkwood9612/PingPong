#pragma once
#include <SDL2\SDL_mixer.h>

#include <memory>
#include <vector>
#include <map>
#include <string>

class AudioStorage
{
public:
	AudioStorage() {};
	AudioStorage(int frequency, Uint16 format, int channels, int chunksize);

	void LoadSoundEffect(const std::string name, const char* path);
	void LoadMusic(const std::string name, const char* path);

	void operator=(const AudioStorage& audioStorage);

	void FreeMusic(const std::string name);
	void FreeAllMusic();

	void FreeSoundEffect(const std::string name);
	void FreeAllSoundEffect();
	
	void PlayMusic(const std::string name, int loops);
	void PlaySoundEffect(const std::string name, int loops);

	const std::string collisionMusicName = "collision";
	const std::string backgroundMusicName = "background";
	const std::string respawnMusicName = "respawn";
	
private:
	using StorageMusic = std::map<std::string, Mix_Music*>;
	using StorageSoundEffect = std::map<std::string, Mix_Chunk*>;

	StorageMusic storageMusic;
	StorageSoundEffect storageSoundEffect;
};