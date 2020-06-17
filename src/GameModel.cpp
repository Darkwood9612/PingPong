#include "GameModel.h"
#include <stdexcept>

GameModel::GameModel(WindowModel& windowModel, SDL_Surface* platformSurface) : SCREEN_HEIGHT(windowModel.SCREEN_HEIGHT) {
	if (!platformSurface)
		throw std::runtime_error("platformSurface == nullptr");

	SDL_Rect playerRect = { int(windowModel.SCREEN_WIDTH * 0.2), int(windowModel.SCREEN_HEIGHT/2 - platformSurface->h /2), platformSurface->w, platformSurface->h};
	SDL_Rect botRect = { int(windowModel.SCREEN_WIDTH * 0.8), int(windowModel.SCREEN_HEIGHT / 2 - platformSurface->h / 2), platformSurface->w, platformSurface->h};
	this->playerPlatform = Platform(playerRect, platformSurface);
	this->botPlatform = Platform(botRect, platformSurface);
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
