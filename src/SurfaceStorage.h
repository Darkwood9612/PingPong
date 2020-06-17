#pragma once
#include <map>
#include <string>

struct SDL_Surface;
class SurfaceStorage
{
public:

	SDL_Surface* LoadBMP(const std::string name, const char* path);
	void SetBMP(const std::string name, SDL_Surface* surface);

	SDL_Surface* GetBMP(const std::string name);
	void FreeSurface(std::string name);
	void FreeAllSurfaces();

private:
	using Storage = std::map<std::string, SDL_Surface*>;
	Storage storage;
};