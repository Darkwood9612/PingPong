#pragma once
#include "Window.h"
#include "SurfaceStorage.h"
#include "Ball.h"
#include "AudioStorage.h"

class GameModel
{
public:
	explicit GameModel(Window& windowModel, SDL_Surface* platformSurface);

	void PlayerPlatformMoveDown();
	void PlayerPlatformMoveUp();
	void BotPlatformMoveDown();
	void BotPlatformMoveUp();
	void MoveBall();

	SDL_Surface GetPlatformBackground();
	SDL_Surface GetBallBackground();
	SDL_Rect GetPlayerRect();
	SDL_Rect GetBotRect();
	SDL_Rect GetBallRect();
	int GetBallSpeed() { return ball.speed; };

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
	SDL_Rect GetScreenCenter() { return screenCenter; };

	AudioStorage audioStorage;

private:
	const std::string playerPointsId = "playerScore";
	const std::string botPointsId = "botScore";
	int playerPoints = 0;
	int botPoints = 0;

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Rect screenCenter;
	
	Ball ball;

	const float X_PLAYER_PLATFORM_OFFSET = 0.1f;
	const float X_BOT_PLATFORM_OFFSET = 0.9f;
	Platform playerPlatform;
	Platform botPlatform;
};