#include "SurfaceStorage.h"
#include <stdexcept>

SurfaceStorage::SurfaceStorage(const char* fontPath, int fontSize)
{
    this->myFont = TTF_OpenFont(fontPath, fontSize);

    if (!this->myFont){
        std::string err = TTF_GetError();
        throw std::runtime_error("Error in function 'TTF_OpenFont': " + err);
    }
}

SDL_Surface* SurfaceStorage::LoadBMP(const std::string name, const char* path)
{
    if (auto surface = SDL_LoadBMP(path)) {
        
        auto findResult = this->storage.find(name);

        findResult == this->storage.end()
            ? this->storage[name] = surface
            : throw std::runtime_error("LoadBMP error: name already exists");

        return surface;
    }
    
    throw std::runtime_error("LoadBMP error: surface == nullptr");
}

void SurfaceStorage::SetBMP(const std::string name, SDL_Surface* surface)
{
    auto findResult = this->storage.find(name);

    if (findResult != this->storage.end()) {
        SDL_FreeSurface(findResult->second);
    }

    this->storage[name] = surface;
}

SDL_Surface* SurfaceStorage::GetBMP(const std::string name)
{
    auto findResult = this->storage.find(name);

    return findResult != this->storage.end()
        ? findResult->second
        : nullptr;
}

void SurfaceStorage::FreeSurface(const std::string name)
{
    auto findResult = this->storage.find(name);

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