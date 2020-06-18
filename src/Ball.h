#pragma once
#include "Platform.h"

class Ball : private Platform
{
public:
	Ball(SDL_Rect _rect, SDL_Surface* _background);
	Ball() {};

	SDL_Rect GetRect();
	SDL_Surface GetBackGround();

	void Respawn();
private:
	float angleOfFlight = 0.f;
};