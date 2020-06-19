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

	void LoadMID(const std::string name, const char* path);

	void operator=(const AudioStorage& audioStorage);

	void FreeMusic(const std::string name);
	void FreeAllMusic();
	void PlayMusic(const std::string name, int loops);

	const std::string collisionMusicName = "collision";

private:
	using Storage = std::map<std::string, Mix_Music*>;
	Storage storage;
};