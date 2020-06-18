#pragma once
#include <SDL_rect.h>
#include <SDL_surface.h>

class Platform
{
public:
	Platform(SDL_Rect _rect, SDL_Surface* _background): rect(_rect), background(_background){};
	Platform();

	SDL_Surface* background;
	SDL_Rect rect;

	int speed = 15;
};