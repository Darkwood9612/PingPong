#include "Controller.h"

Controller::Controller(void)
{
}

void Controller::UpdateModel(GameModel& model)
{
    if (!SDL_PollEvent(&event))
        return;

    switch (event.type){
        case SDL_QUIT:
            model.needCloseGame = true;
            break; 
        case SDL_KEYDOWN:
            KeyDown(event.key.keysym, model);
            break;
        default:
            break;
    }
}

void Controller::KeyDown(SDL_Keysym& s, GameModel& model)
{
    switch (s.sym)
    {
    case SDLK_UP:
        model.PlayerPlatformMoveUp();
        break;
    case SDLK_DOWN:
        model.PlayerPlatformMoveDown();
        break;
    default:
        break;
    }
}
