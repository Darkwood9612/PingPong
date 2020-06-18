#include "Ball.h"
#include <vector>
#include <math.h>

namespace {
    constexpr double PI = 3.14159265358979323846;

    SDL_Rect GetPositionPointOnCircle(float radius,
        const SDL_Rect& centrPos,
        float degrees)
    {
        float radian = degrees * (PI / 180);
        float x = radius * cos(radian) + centrPos.x;
        float y = radius * sin(radian) + centrPos.y;

        return { int(x), int(y),0,0 };
    }
}

Ball::Ball(SDL_Rect _rect, SDL_Surface* background)
{
	this->rect = _rect;
	this->background = background;
    this->speed = 3;
}

void Ball::Respawn(SDL_Rect spawnPoint)
{
	rect = spawnPoint;
    angleOfFlight = 112.f;
}

void Ball::Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, std::function<void(void)> soundCallback, std::function<void(bool)> scoreCallback)
{
    auto nextPoint = GetPositionPointOnCircle(1 * speed, rect, angleOfFlight);

    if (nextPoint.x > 0 && nextPoint.x < SCREEN_WIDTH && nextPoint.y > 0 && nextPoint.y < SCREEN_HEIGHT) {

        rect = nextPoint;
        return;
    }

    if (nextPoint.x <= 0 || nextPoint.x >= SCREEN_WIDTH) {
        
        angleOfFlight = 180 - angleOfFlight;
        angleOfFlight = angleOfFlight < 0 ? angleOfFlight += 360 : angleOfFlight;

        rect = GetPositionPointOnCircle(1 * speed, rect, angleOfFlight);
        soundCallback();
        scoreCallback(nextPoint.x <= 0 ? false: true);
        return;
    }


    if (nextPoint.y <= 0 || nextPoint.y >= SCREEN_HEIGHT) {
        
        angleOfFlight = 360 - angleOfFlight;
        rect = GetPositionPointOnCircle(1 * speed, rect, angleOfFlight);
        soundCallback();
        return;
    }
}
