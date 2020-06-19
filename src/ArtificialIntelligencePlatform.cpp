#include "ArtificialIntelligencePlatform.h"
#include "Ball.h"

ArtificialIntelligencePlatform::ArtificialIntelligencePlatform(SDL_Rect _rect, SDL_Surface* _background)
{
	this->rect = _rect;
	this->background = background;
}

ArtificialIntelligencePlatform::ArtificialIntelligencePlatform()
{
		rect = SDL_Rect();
		background = nullptr;
}

void ArtificialIntelligencePlatform::HitBall(const int SCREEN_HEIGHT, float angleBallFlight, SDL_Rect ballRect)
{	
	TryCatchBall(SCREEN_HEIGHT, CalculateBallTrajectory(angleBallFlight, ballRect));
}

SDL_Rect ArtificialIntelligencePlatform::CalculateBallTrajectory(float angleBallFlight, SDL_Rect ballRect)
{
	float radius = rect.x - ballRect.x;
	return Ball::GetPositionPointOnCircle(radius , ballRect, angleBallFlight);
}

void ArtificialIntelligencePlatform::TryCatchBall(const int SCREEN_HEIGHT, SDL_Rect ballPointTarget)
{	
	auto halfHeight = rect.h / 2;
	ballPointTarget.y -= rand() % halfHeight;

	auto STEP = 5;
	auto centrPlatformY = rect.y + halfHeight;
	bool abovePoint = ballPointTarget.y <= centrPlatformY - halfHeight;
	bool belowPoint = ballPointTarget.y >= centrPlatformY + halfHeight;

		if (abovePoint)
			(rect.y - STEP > 0) ? rect.y -= STEP : NULL;

		if (belowPoint)
			(rect.y + STEP + rect.h < SCREEN_HEIGHT) ? rect.y += STEP : NULL;
}
