#include "SurfaceStorage.h"
#include <SDL2\SDL_surface.h>
#include <stdexcept>

SDL_Surface* SurfaceStorage::LoadBMP(const std::string name, const char* path)
{
    if (auto surface = SDL_LoadBMP(path)) {
        
        auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SDL_Surface*>& item) {
            return item.first == name;
        });

        findResult == this->storage.end()
            ? this->storage[name] = surface
            : throw std::runtime_error("LoadBMP error: name already exists");

        return surface;
    }
    
    throw std::runtime_error("LoadBMP error: result == nullptr");
}

void SurfaceStorage::SetBMP(const std::string name, SDL_Surface* surface)
{
    this->storage[name] = surface;
}

SDL_Surface* SurfaceStorage::GetBMP(const std::string name)
{
    auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SDL_Surface*>& item) {
        return item.first == name;
        });

    return findResult != this->storage.end()
        ? findResult->second
        : nullptr;
}

void SurfaceStorage::FreeSurface(const std::string name)
{
    auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SDL_Surface*>& item) {
        return item.first == name;
        });

    if (findResult != this->storage.end()) {
        SDL_FreeSurface(findResult->second);
        this->storage.erase(findResult);
    }
        
}

void SurfaceStorage::FreeAllSurfaces()
{
    for (auto& item : this->storage)
        SDL_FreeSurface(item.second);

    this->storage.clear();
}