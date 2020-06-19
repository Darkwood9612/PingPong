#pragma once
#include "Platform.h"

class ArtificialIntelligencePlatform :public Platform
{
public:

	ArtificialIntelligencePlatform(SDL_Rect _rect, SDL_Surface* _background);
	ArtificialIntelligencePlatform();

	void operator=(const ArtificialIntelligencePlatform& platformAI);
	
	void HitBall(const int SCREEN_HEIGHT, float angleBallFlight, SDL_Rect ballRect);
private:
	const int STEP = 3;
	void TryCatchBall(const int SCREEN_HEIGHT, float angleBallFlight, SDL_Rect ballPointTarget);
};