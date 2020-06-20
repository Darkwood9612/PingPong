#pragma once
#include <SDL_rect.h>
#include <SDL_surface.h>

class Platform
{
public:
  Platform(){};
  Platform(SDL_Rect _rect, SDL_Surface* _background)
    : rect(_rect)
    , background(_background){};

  SDL_Surface* background = nullptr;
  SDL_Rect rect = { 0, 0, 0, 0 };

  int speed = 12;
};