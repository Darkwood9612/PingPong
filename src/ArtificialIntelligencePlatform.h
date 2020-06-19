#pragma once
#include "Platform.h"

class ArtificialIntelligencePlatform :public Platform
{
public:

	ArtificialIntelligencePlatform(SDL_Rect _rect, SDL_Surface* _background);
	ArtificialIntelligencePlatform();

	void HitBall(const int SCREEN_HEIGHT, float angleBallFlight, SDL_Rect ballRect);
private:

	SDL_Rect CalculateBallTrajectory(float angleBallFlight, SDL_Rect ballRect);
	void TryCatchBall(const int SCREEN_HEIGHT, SDL_Rect ballPointTarget);
};