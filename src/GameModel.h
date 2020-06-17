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

	SDL_Surface* dividingStrip = nullptr;

	void SetSpeed(int newSpeed) { this->speed = newSpeed > 0 ? this->speed : 10; };

	void AddPointToPlayer() { ++this->playerPoints; };
	void AddPointToBot() { ++this->botPoints; };

	int GetPlayerScore() { return this->playerPoints; };
	int GetBotScore() { return this->botPoints; };
private:
	int playerPoints = 0;
	int botPoints = 0;

	const int SCREEN_HEIGHT;
	int speed = 10;
	Platform playerPlatform;
	Platform botPlatform;
};