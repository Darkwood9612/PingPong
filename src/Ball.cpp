#include "Ball.h"
#include <vector>

namespace {
    SDL_Rect GetPositionPointOnCircle(float radius,
        const SDL_Rect& centrPos,
        float degrees)
    {
        float radian = degrees * (acosf(-1) / 180);
        float x = radius * cos(radian) + centrPos.x;
        float y = radius * sin(radian) + centrPos.y;

        return { int(x), int(y),0,0 };
    }
}

Ball::Ball(SDL_Rect _rect, SDL_Surface* _background)
{
	this->rect = _rect;
	this->background = _background;
}

void Ball::Respawn(SDL_Rect spawnPoint)
{
	rect = spawnPoint;
}

void Ball::Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    auto nextPoint = GetPositionPointOnCircle(1 * speed, rect, angleOfFlight);

    if (nextPoint.x > 0 && nextPoint.x < SCREEN_WIDTH && nextPoint.y > 0 && nextPoint.y < SCREEN_HEIGHT) {

        rect = nextPoint;
        return;
    }

    //angleOfFlight = angleOfFlight > 180 ? (180 - angleOfFlight)*-1 :180 - angleOfFlight;
}
