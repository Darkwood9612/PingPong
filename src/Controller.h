#pragma once
#include "GameModel.h"
#include <SDL2\SDL_events.h>

class Controller
{
public:
	Controller(void);

	void UpdateModel(GameModel& model);
	

private:
	void KeyDown(SDL_Keysym& s, GameModel& model);
	SDL_Event event;
};