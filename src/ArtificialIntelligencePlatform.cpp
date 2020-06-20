#include "ArtificialIntelligencePlatform.h"
#include "Ball.h"

void ArtificialIntelligencePlatform::operator=(
  const ArtificialIntelligencePlatform& platformAI)
{
  this->rect = platformAI.rect;
  this->background = platformAI.background;
  this->speed = platformAI.speed;
}

void ArtificialIntelligencePlatform::HitBall(const int SCREEN_HEIGHT,
                                             float angleBallFlight,
                                             SDL_Rect ballRect)
{
  TryCatchBall(SCREEN_HEIGHT, angleBallFlight, ballRect);
}

void ArtificialIntelligencePlatform::TryCatchBall(const int SCREEN_HEIGHT,
                                                  float angleBallFlight,
                                                  SDL_Rect ballPointTarget)
{
  bool isBallFlightDown = 360 - angleBallFlight > 180;
  bool isBallFlightToPlayer =
    isBallFlightDown ? angleBallFlight > 90 : angleBallFlight < 270;

  if (isBallFlightToPlayer)
    return;

  int randoOffset = rand() % rect.h;
  isBallFlightDown ? ballPointTarget.y += randoOffset
                   : ballPointTarget.y -= randoOffset;

  int halfHeight = rect.h / 2;
  auto centrPlatformY = rect.y + halfHeight;
  bool abovePoint = ballPointTarget.y <= centrPlatformY - halfHeight;
  bool belowPoint = ballPointTarget.y >= centrPlatformY + halfHeight;

  if (abovePoint)
    (rect.y - STEP > 0) ? rect.y -= STEP : NULL;

  if (belowPoint)
    (rect.y + STEP + rect.h < SCREEN_HEIGHT) ? rect.y += STEP : NULL;
}
