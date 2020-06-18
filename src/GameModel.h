#pragma once
#include "Window.h"
#include "SurfaceStorage.h"
#include "Ball.h"

class GameModel
{
public:
	explicit GameModel(Window& windowModel, SDL_Surface* platformSurface);

	void PlayerPlatformMoveDown();
	void PlayerPlatformMoveUp();
	void BotPlatformMoveDown();
	void BotPlatformMoveUp();

	SDL_Surface GetPlatformBackground();
	SDL_Rect GetPlayerRect();
	SDL_Rect GetBotRect();

	bool needCloseGame = false;

	SDL_Surface* dividingStrip = nullptr;

	void SetPlatformsSpeed(int newSpeed);

	void AddPointToPlayer() { ++this->playerPoints; };
	void AddPointToBot() { ++this->botPoints; };

	int GetPlayerScore() { return this->playerPoints; };
	int GetBotScore() { return this->botPoints; };

	SDL_Surface* GetPlayerScoreSurface(int windowScore, SurfaceStorage& surfaceStorage);
	SDL_Surface* GetBotScoreSurface(int windowScore, SurfaceStorage& surfaceStorage);
	Ball ball;
private:
	const std::string playerPointsId = "playerScore";
	const std::string botPointsId = "botScore";
	int playerPoints = 0;
	int botPoints = 0;

	const int SCREEN_HEIGHT;

	Platform playerPlatform;
	Platform botPlatform;
};