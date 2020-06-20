#pragma once
#include "GameModel.h"
#include <SDL2\SDL_events.h>
#include <ctime>

class Controller
{
public:
  void UpdateModel(GameModel& model);

private:
  const int BALL_UPDATE_PAUSE = 300;
  void KeyDown(SDL_Keysym& s, GameModel& model);
  SDL_Event event;
  clock_t lastApply = 0;
};