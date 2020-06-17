#pragma once
#include "Platform.h"
#include "Window.h"

class GameModel
{
public:
	GameModel(WindowModel& windowModel, SDL_Surface* platformSurface);

	void PlayerPlatformMoveDown();
	void PlayerPlatformMoveUp();

	SDL_Surface GetPlatformBackground();
	SDL_Rect GetPlayerRect();
	SDL_Rect GetBotRect();

	bool needCloseGame = false;

	SDL_Surface* dividingStrip = nullptr;;

	SDL_Surface* playerPoints = nullptr;
	SDL_Surface* botPoints = nullptr;;

	void SetSpeed(int newSpeed) { this->speed = newSpeed; };

private:
	const int SCREEN_HEIGHT;
	int speed = 10;
	Platform playerPlatform;
	Platform botPlatform;
};