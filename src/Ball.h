#pragma once
#include "Platform.h"
#include <functional>

class Ball : public Platform
{
public:
	Ball(SDL_Rect _rect, SDL_Surface* _background);
	Ball() {};

	void Respawn(SDL_Rect spawnPoint);
	void Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, std::function<void(void)> soundCallback, std::function<void(bool)> scoreCallback);
private:
	float angleOfFlight = 112.f;
};