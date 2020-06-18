#include "Controller.h"


void Controller::UpdateModel(GameModel& model)
{
    if (clock() - lastApply > BALL_UPDATE_PAUSE / model.GetBallSpeed()) {
        model.MoveBall();
        lastApply = clock();
    }

    while (SDL_PollEvent(&event)) {

        switch (event.type) {
        case SDL_QUIT:
            model.needCloseGame = true;
            break;
        case SDL_KEYDOWN:
            KeyDown(event.key.keysym, model);
            break;
        default:
            return;
        }
    }
}

void Controller::KeyDown(SDL_Keysym& s, GameModel& model)
{
    switch (s.sym)
    {
    case SDLK_UP:
        model.PlayerPlatformMoveUp();
        model.BotPlatformMoveUp();
        break;
    case SDLK_DOWN:
        model.PlayerPlatformMoveDown();
        model.BotPlatformMoveDown();
        break;
    default:
        break;
    }
}
