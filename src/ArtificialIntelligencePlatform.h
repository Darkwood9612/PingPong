#pragma once
#include "Platform.h"

class ArtificialIntelligencePlatform : public Platform
{
public:
  ArtificialIntelligencePlatform(){};
  ArtificialIntelligencePlatform(SDL_Rect _rect, SDL_Surface* _background)
    : Platform(_rect, _background){};

  void operator=(const ArtificialIntelligencePlatform& platformAI);

  void HitBall(const int SCREEN_HEIGHT, float angleBallFlight,
               SDL_Rect ballRect);

private:
  const int STEP = 3;
  void TryCatchBall(const int SCREEN_HEIGHT, float angleBallFlight,
                    SDL_Rect ballPointTarget);
};