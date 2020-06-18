#include "GameModel.h"

#include <stdexcept>
#include <sstream>
#include <string>

namespace {

    std::string IntToString(int n) {
        std::stringstream sstream;
        sstream << n;
        return sstream.str();
    }

    SDL_Surface* ScoreToSurface(int number, const std::string& name, SurfaceStorage& surfaceStorage) {

        std::string score = IntToString(number);
        auto scoreImage = TTF_RenderText_Solid(surfaceStorage.GetFont(), score.c_str(), surfaceStorage.GetWhite());

        if (!scoreImage) {
            std::string err = TTF_GetError();
            throw std::runtime_error("Error in function 'TTF_RenderText_Solid': " + err);
        }

        surfaceStorage.SetBMP(name, scoreImage);
        return scoreImage;
    }

    SDL_Surface* GetScoreSurface(int gameScore, int windowScore, const std::string name, SurfaceStorage& surfaceStorage) {
        return gameScore != windowScore
            ? ScoreToSurface(gameScore, name, surfaceStorage)
            : surfaceStorage.GetBMP(name);
    };
}

GameModel::GameModel(Window& window, SDL_Surface* platformSurface) : SCREEN_HEIGHT(window.SCREEN_HEIGHT) {
	if (!platformSurface)
		throw std::runtime_error("platformSurface == nullptr");

	SDL_Rect playerRect = { int(window.SCREEN_WIDTH * 0.2), int(window.SCREEN_HEIGHT/2 - platformSurface->h /2), platformSurface->w, platformSurface->h};
	SDL_Rect botRect = { int(window.SCREEN_WIDTH * 0.8), int(window.SCREEN_HEIGHT / 2 - platformSurface->h / 2), platformSurface->w, platformSurface->h};
	playerPlatform = Platform(playerRect, platformSurface);
	botPlatform = Platform(botRect, platformSurface);
};

void GameModel::PlayerPlatformMoveDown()
{
	if (playerPlatform.rect.y + playerPlatform.rect.h < SCREEN_HEIGHT)
		playerPlatform.rect.y = playerPlatform.rect.y + 1 * playerPlatform.speed;
}

void GameModel::PlayerPlatformMoveUp()
{
	if (playerPlatform.rect.y > 0)
		playerPlatform.rect.y = playerPlatform.rect.y - 1 * playerPlatform.speed;
}

void GameModel::BotPlatformMoveDown()
{
    if (botPlatform.rect.y + botPlatform.rect.h < SCREEN_HEIGHT)
        botPlatform.rect.y = botPlatform.rect.y + 1 * botPlatform.speed;
}

void GameModel::BotPlatformMoveUp()
{
    if (botPlatform.rect.y > 0)
        botPlatform.rect.y = botPlatform.rect.y - 1 * botPlatform.speed;
}

SDL_Surface GameModel::GetPlatformBackground()
{
	return playerPlatform.background ? *playerPlatform.background : SDL_Surface();
}

SDL_Rect GameModel::GetPlayerRect()
{
	return playerPlatform.rect;
}

SDL_Rect GameModel::GetBotRect()
{
	return botPlatform.rect;
}

void GameModel::SetPlatformsSpeed(int newSpeed)
{
    playerPlatform.speed = newSpeed;
    botPlatform.speed = newSpeed;
}

SDL_Surface* GameModel::GetPlayerScoreSurface(int windowScore, SurfaceStorage& surfaceStorage)
{
        return playerPoints != windowScore
            ? ScoreToSurface(playerPoints, playerPointsId, surfaceStorage)
            : surfaceStorage.GetBMP(playerPointsId);
}

SDL_Surface* GameModel::GetBotScoreSurface(int windowScore, SurfaceStorage& surfaceStorage)
{
    return botPoints != windowScore
        ? ScoreToSurface(botPoints, botPointsId, surfaceStorage)
        : surfaceStorage.GetBMP(botPointsId);
}
