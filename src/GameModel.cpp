#include "GameModel.h"
#include "SurfaceStorage.h"

GameModel::GameModel(const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT, SurfaceStorage::SurfaceData surfaceData) :
	SCREEN_WIDTH(_SCREEN_WIDTH), SCREEN_HEIGHT(_SCREEN_HEIGHT) {
	SDL_Rect playerRect = { int(_SCREEN_WIDTH * 0.2), int(_SCREEN_HEIGHT/2 - surfaceData.height /2),surfaceData.width,surfaceData.height };
	SDL_Rect botRect = { int(_SCREEN_WIDTH * 0.8), int(_SCREEN_HEIGHT / 2 - surfaceData.height / 2),surfaceData.width,surfaceData.height };
	this->playerPlatform = Platform(playerRect, surfaceData.surface);
	this->botPlatform = Platform(botRect, surfaceData.surface);
};

void GameModel::PlayerPlatformMoveDown()
{
	if (playerPlatform.rect.y + playerPlatform.rect.h < this->SCREEN_HEIGHT)
		playerPlatform.rect.y = playerPlatform.rect.y + 1 * this->speed;
}

void GameModel::PlayerPlatformMoveUp()
{
	if (playerPlatform.rect.y > 0)
		playerPlatform.rect.y = playerPlatform.rect.y - 1 * this->speed;
}

SDL_Surface GameModel::GetPlatformBackground()
{
	return this->playerPlatform.background ? *this->playerPlatform.background : SDL_Surface();
}

SDL_Rect GameModel::GetPlayerRect()
{
	return this->playerPlatform.rect;
}

SDL_Rect GameModel::GetBotRect()
{
	return this->botPlatform.rect;
}
