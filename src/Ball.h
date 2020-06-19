#pragma once
#include "Platform.h"
#include <functional>

class Ball : public Platform
{
public:

	static SDL_Rect GetPositionPointOnCircle(float radius,
		const SDL_Rect& centrPos,
		float degrees);

	explicit Ball(SDL_Rect _rect, SDL_Surface* _background);
	Ball() {};

	void operator=(const Ball& ball);
	float GetAngleOfFlight() { return angleOfFlight; };

	void Respawn(SDL_Rect spawnPoint, bool isPlayerLose);
	void Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, SDL_Rect playerRect, SDL_Rect botRect, std::function<void(void)> soundCallback, std::function<void(bool)> scoreCallback);
private:
	int STEP = 5;
	float angleOfFlight = 315.f;
};