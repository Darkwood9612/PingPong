#pragma once
#include <SDL2\SDL_surface.h>
#include <SDL2\SDL_ttf.h>

#include <map>
#include <string>

class SurfaceStorage
{
public:
  SurfaceStorage(const char* fontPath, int fontSize);

  SDL_Surface* LoadBMP(const std::string name, const char* path);

  void SetBMP(const std::string name, SDL_Surface* surface);
  SDL_Surface* GetBMP(const std::string name);

  void FreeSurface(const std::string name);
  void FreeAllSurfaces();

  TTF_Font* GetFont() { return this->myFont; };
  SDL_Color GetWhite() { return this->colorWhite; };
  SDL_Color GetBlack() { return this->colorBlack; };

private:
  using Storage = std::map<std::string, SDL_Surface*>;

  SDL_Color colorWhite = { 255, 255, 255 };
  SDL_Color colorBlack = { 0, 0, 0 };

  TTF_Font* myFont = nullptr;
  Storage storage;
};