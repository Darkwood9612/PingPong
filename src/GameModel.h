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
	void MoveBall();
	void RespawnBall() { ball.Respawn(screenCenter); };

	SDL_Surface GetPlatformBackground();
	SDL_Surface GetBallBackground();
	SDL_Rect GetPlayerRect();
	SDL_Rect GetBotRect();
	SDL_Rect GetBallRect();

	bool needCloseGame = false;

	SDL_Surface* dividingStrip = nullptr;

	void SetGameSpeed(int newSpeed);

	void AddPointToPlayer() { ++this->playerPoints; };
	void AddPointToBot() { ++this->botPoints; };

	int GetPlayerScore() { return this->playerPoints; };
	int GetBotScore() { return this->botPoints; };

	SDL_Surface* GetPlayerScoreSurface(int windowScore, SurfaceStorage& surfaceStorage);
	SDL_Surface* GetBotScoreSurface(int windowScore, SurfaceStorage& surfaceStorage);
	void CreateBall(SDL_Surface* background, SDL_Rect rect = SDL_Rect());
private:
	const std::string playerPointsId = "playerScore";
	const std::string botPointsId = "botScore";
	int playerPoints = 0;
	int botPoints = 0;

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Rect screenCenter;
	
	Ball ball;
	Platform playerPlatform;
	Platform botPlatform;
};