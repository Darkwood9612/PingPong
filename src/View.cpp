#include "View.h"
#include <SDL2\SDL_surface.h>
#include <SDL2\SDL_video.h>

View::View(void)
{
}

void View::Draw(GameModel& gameModel, WindowModel& windowModel)
{
    SDL_FillRect(windowModel.screen, NULL, SDL_MapRGB(windowModel.screen->format, 0, 0, 0));

    SDL_Surface platformBackground = gameModel.GetPlatformBackground();

    SDL_Rect playerRect = gameModel.GetPlayerRect();
    SDL_Rect botRect = gameModel.GetBotRect();

    auto infelicity = gameModel.dividingStrip ? gameModel.dividingStrip->w / 2 : 0;
    SDL_Rect centerRect = { int(windowModel.SCREEN_WIDTH / 2 - infelicity), 0, 0, 0};

    SDL_BlitSurface(gameModel.dividingStrip, NULL, windowModel.screen, &centerRect);
    SDL_BlitSurface(&platformBackground, NULL, windowModel.screen, &playerRect);
    SDL_BlitSurface(&platformBackground, NULL, windowModel.screen, &botRect);

    SDL_UpdateWindowSurface(windowModel.window);
}
