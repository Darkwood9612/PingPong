#include "View.h"
#include <SDL2\SDL_surface.h>
#include <SDL2\SDL_video.h>

View::View(void)
{
}

void View::Draw(GameModel& model)
{
    SDL_FillRect(model.screen, NULL, SDL_MapRGB(model.screen->format, 0, 0, 0));

    SDL_Surface platformBackground = model.GetPlatformBackground();

    SDL_Rect playerRect = model.GetPlayerRect();
    SDL_Rect botRect = model.GetBotRect();

    SDL_BlitSurface(&platformBackground, NULL, model.screen, &playerRect);
    SDL_BlitSurface(&platformBackground, NULL, model.screen, &botRect);

    SDL_UpdateWindowSurface(model.window);
}
