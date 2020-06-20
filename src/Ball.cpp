#include "Ball.h"
#include <vector>
#include <math.h>

namespace {
    constexpr double PI = 3.14159265358979323846;
}

SDL_Rect Ball::GetPositionPointOnCircle(float radius, const SDL_Rect& centrPos, float degrees)
{
    srand(time(0));
    float radian = degrees * (PI / 180);
    float x = radius * cos(radian) + centrPos.x;
    float y = radius * sin(radian) + centrPos.y;

    return { int(x), int(y),0,0 };
}

Ball::Ball(SDL_Rect _rect, SDL_Surface* background)
{
    srand(time(0));
	this->rect = _rect;
	this->background = background;
}

void Ball::operator=(const Ball& ball)
{
    this->angleOfFlight = ball.angleOfFlight;
    this->background = ball.background;
    this->rect = ball.rect;
    this->speed = ball.speed;
    this->STEP = ball.STEP;
}

void Ball::Respawn(SDL_Rect spawnPoint, bool isPlayerLose)
{
	rect = spawnPoint;
    float randNum = rand() % 90;
    randNum = randNum < 10 ? 10 : randNum;

    angleOfFlight = isPlayerLose ? 135.f + randNum : 405.f -( randNum > 45.f ? randNum : randNum +360.f);
}

void Ball::Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, SDL_Rect playerRect, SDL_Rect botRect, std::function<void(void)> collisionCallback, std::function<void(bool)> scoreCallback)
{
    auto nextPoint = GetPositionPointOnCircle(STEP, rect, angleOfFlight);
    
    if (nextPoint.x <= playerRect.x + playerRect.w &&
        nextPoint.x >= playerRect.x &&
        nextPoint.y >= playerRect.y &&
        nextPoint.y <= playerRect.y + playerRect.h) {

        collisionCallback();

        angleOfFlight = 180 - angleOfFlight;
        angleOfFlight = angleOfFlight < 0 ? angleOfFlight += 360 : angleOfFlight;

        rect = GetPositionPointOnCircle(STEP, rect, angleOfFlight);
        return;
    }

    if (nextPoint.x <= botRect.x + botRect.w &&
        nextPoint.x >= botRect.x &&
        nextPoint.y >= botRect.y &&
        nextPoint.y <= botRect.y + botRect.h) {
        
        collisionCallback();
        
        angleOfFlight = 180 - angleOfFlight;
        angleOfFlight = angleOfFlight < 0 ? angleOfFlight += 360 : angleOfFlight;

        rect = GetPositionPointOnCircle(STEP, rect, angleOfFlight);
        return;
    }

    if (nextPoint.x <= 1 || nextPoint.x >= SCREEN_WIDTH - 1) {

        angleOfFlight = 180 - angleOfFlight;
        angleOfFlight = angleOfFlight < 0 ? angleOfFlight += 360 : angleOfFlight;

        rect = GetPositionPointOnCircle(STEP, rect, angleOfFlight);
        collisionCallback();
        scoreCallback(nextPoint.x <= 0 ? false : true);
        return;
    }


    if (nextPoint.y <= 1 || nextPoint.y >= SCREEN_HEIGHT - 1) {

        angleOfFlight = 360 - angleOfFlight;

        rect = GetPositionPointOnCircle(STEP, rect, angleOfFlight);
        collisionCallback();
        return;
    }

    if (nextPoint.x > 0 && nextPoint.x < SCREEN_WIDTH && nextPoint.y > 0 && nextPoint.y < SCREEN_HEIGHT) {

        rect = nextPoint;
        return;
    }
}
