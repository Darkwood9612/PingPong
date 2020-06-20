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

GameModel::GameModel(Window& window, SDL_Surface* platformSurface) : SCREEN_HEIGHT(window.SCREEN_HEIGHT), SCREEN_WIDTH(window.SCREEN_WIDTH) {
	if (!platformSurface)
		throw std::runtime_error("platformSurface == nullptr");

	SDL_Rect playerRect = { int(window.SCREEN_WIDTH * X_PLAYER_PLATFORM_OFFSET), int(window.SCREEN_HEIGHT/2 - platformSurface->h /2), platformSurface->w, platformSurface->h};
	SDL_Rect botRect = { int(window.SCREEN_WIDTH * X_BOT_PLATFORM_OFFSET), int(window.SCREEN_HEIGHT / 2 - platformSurface->h / 2), platformSurface->w, platformSurface->h};
	playerPlatform = Platform(playerRect, platformSurface);
	botPlatform = ArtificialIntelligencePlatform(botRect, platformSurface);
    screenCenter.x = window.SCREEN_WIDTH / 2;
    screenCenter.y = window.SCREEN_HEIGHT / 2;
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

void GameModel::BotPlatformMove()
{
    botPlatform.HitBall(SCREEN_HEIGHT, ball.GetAngleOfFlight(), ball.rect);
}

void GameModel::MoveBall()
{
    ball.Move(SCREEN_WIDTH, SCREEN_HEIGHT, GetPlayerRect(), GetBotRect(),
        [&]() {
            audioStorage.PlaySoundEffect(audioStorage.collisionMusicName, 0);
        },
        [&](bool isPlayerWin){
        isPlayerWin ? this->AddPointToPlayer() : this->AddPointToBot();
        ball.Respawn(screenCenter, isPlayerWin);
        audioStorage.PlaySoundEffect(audioStorage.respawnMusicName, 0);
    });
}

SDL_Surface GameModel::GetPlatformBackground()
{
	return playerPlatform.background ? *playerPlatform.background : SDL_Surface();
}

SDL_Surface GameModel::GetBallBackground()
{
    return ball.background ? *ball.background : SDL_Surface();;
}

SDL_Rect GameModel::GetPlayerRect()
{
	return playerPlatform.rect;
}

SDL_Rect GameModel::GetBotRect()
{
	return botPlatform.rect;
}

SDL_Rect GameModel::GetBallRect()
{
    return ball.rect;
}

void GameModel::SetGameSpeed(int newSpeed)
{
    playerPlatform.speed = newSpeed;
    botPlatform.speed = newSpeed;
    ball.speed = newSpeed;
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

void GameModel::CreateBall(SDL_Surface* background, SDL_Rect rect)
{
    ball = Ball(rect, background);
}
