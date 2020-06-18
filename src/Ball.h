#pragma once
#include "Platform.h"

class Ball : public Platform
{
public:
	Ball(SDL_Rect _rect, SDL_Surface* _background);
	Ball() {};

	void Respawn(SDL_Rect spawnPoint);
	void Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
private:
	float angleOfFlight = 10.f;
};