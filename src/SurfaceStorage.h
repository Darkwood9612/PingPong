#pragma once
#include <map>
#include <string>

struct SDL_Surface;
class SurfaceStorage
{
public:
	
	struct SurfaceData {
		SDL_Surface* surface = nullptr;
		int width, height;
	};

	SurfaceStorage::SurfaceData LoadBMP(const std::string name, const char* path, int width, int height);
	SurfaceStorage::SurfaceData GetBMP(const std::string name);
	void FreeSurface(std::string name);
	void FreeAllSurfaces();

private:
	using Storage = std::map<std::string, SurfaceData>;
	Storage storage;
};