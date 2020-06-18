#include <SDL2\SDL_ttf.h>

#include "View.h"
#include "SurfaceStorage.h" 

View::View() {};

void View::DrawScore(GameModel& gameModel, Window& window, SurfaceStorage& surfaceStorage)
{
    SDL_Surface* ScoreImage = gameModel.GetPlayerScoreSurface(window.windowPlayerScore, surfaceStorage);
    window.windowPlayerScore = gameModel.GetPlayerScore();

    SDL_Rect rect = window.GetPlayerScoreRect();
    rect.x -= ScoreImage->w;
    SDL_BlitSurface(ScoreImage, NULL, window.screen, &rect);


    ScoreImage = gameModel.GetBotScoreSurface(window.windowBotScore, surfaceStorage);
    window.windowBotScore = gameModel.GetBotScore();

    rect = window.GetBotScoreRect();
    SDL_BlitSurface(ScoreImage, NULL, window.screen, &rect);
}

void View::Draw(GameModel& gameModel, Window& window, SurfaceStorage& surfaceStorage)
{
    window.SetDividingStripXOffset(gameModel.dividingStrip
        ? gameModel.dividingStrip->w / 2 : 0);

    SDL_FillRect(window.screen, NULL, SDL_MapRGB(window.screen->format, 0, 0, 0));

    SDL_Surface platformBackground = gameModel.GetPlatformBackground();
    SDL_Surface ballBackground = gameModel.GetBallBackground();

    SDL_Rect playerRect = gameModel.GetPlayerRect();
    SDL_Rect botRect = gameModel.GetBotRect();
    SDL_Rect dividingStripRect = window.GetDividingStripRect();
    SDL_Rect ballRect = gameModel.GetBallRect();

    SDL_BlitSurface(gameModel.dividingStrip, NULL, window.screen, &dividingStripRect);
    SDL_BlitSurface(&platformBackground, NULL, window.screen, &playerRect);
    SDL_BlitSurface(&platformBackground, NULL, window.screen, &botRect);
    SDL_BlitSurface(&ballBackground, NULL, window.screen, &ballRect);

    DrawScore(gameModel, window, surfaceStorage);

    SDL_UpdateWindowSurface(window.window);
}
