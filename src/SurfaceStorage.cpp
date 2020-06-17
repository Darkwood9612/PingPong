#include "SurfaceStorage.h"
#include <SDL2\SDL_surface.h>
#include <stdexcept>

SurfaceStorage::SurfaceData SurfaceStorage::LoadBMP(const std::string name, const char* path, int width, int height)
{
    if (auto surface = SDL_LoadBMP(path)) {
        
        auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SurfaceData>& item) {
            return item.first == name;
        });

        SurfaceStorage::SurfaceData res = { surface , width, height};

        findResult == this->storage.end()
            ? this->storage[name] = res
            : throw std::runtime_error("LoadBMP error: name already exists");

        return res;
    }
    
    throw std::runtime_error("LoadBMP error: result == nullptr");
}

SurfaceStorage::SurfaceData SurfaceStorage::GetBMP(const std::string name)
{
    auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SurfaceData>& item) {
        return item.first == name;
        });

    return findResult != this->storage.end()
        ? findResult->second
        : SurfaceStorage::SurfaceData();
}

void SurfaceStorage::FreeSurface(const std::string name)
{
    auto findResult = std::find_if(this->storage.begin(), this->storage.end(), [&name](std::pair<const std::string, SurfaceData>& item) {
        return item.first == name;
        });

    if (findResult != this->storage.end()) {
        SDL_FreeSurface(findResult->second.surface);
        this->storage.erase(findResult);
    }
        
}

void SurfaceStorage::FreeAllSurfaces()
{
    for (auto& item : this->storage)
        SDL_FreeSurface(item.second.surface);

    this->storage.clear();
}