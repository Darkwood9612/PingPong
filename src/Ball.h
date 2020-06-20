#pragma once
#include "Platform.h"
#include <functional>
#include <time.h>

class Ball : public Platform
{
public:
  SDL_Rect GetPositionPointOnCircle(float radius, const SDL_Rect& centrPos,
                                    float degrees);

  Ball(){};
  Ball(SDL_Rect _rect, SDL_Surface* _background)
    : Platform(_rect, _background){};

  void operator=(const Ball& ball);
  float GetAngleOfFlight() { return angleOfFlight; };

  void Respawn(SDL_Rect spawnPoint, bool isPlayerLose);

  void Move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT,
            SDL_Rect playerRect, SDL_Rect botRect,
            std::function<void(void)> collisionCallback,
            std::function<void(bool)> scoreCallback);

private:
  int STEP = 5;
  float angleOfFlight = 20.f;
};