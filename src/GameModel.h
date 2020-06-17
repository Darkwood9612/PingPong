#pragma once
#include "Platform.h"
#include <SDL2\SDL_video.h>
#include "SurfaceStorage.h"

class GameModel
{
public:
	GameModel(const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT, SurfaceStorage::SurfaceData surfaceData);

	void PlayerPlatformMoveDown();
	void PlayerPlatformMoveUp();

	SDL_Surface GetPlatformBackground();
	SDL_Rect GetPlayerRect();
	SDL_Rect GetBotRect();

	bool needExitGame = false;
	SDL_Surface* screen = nullptr;
	SDL_Window* window = nullptr;

	void SetSpeed(int newSpeed) { this->speed = newSpeed; };
private:

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	int speed = 10;
	Platform playerPlatform;
	Platform botPlatform;
};