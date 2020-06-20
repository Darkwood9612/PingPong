#include "Window.h"

Window::Window(const char* title, uint32_t windowFlags,
               const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT)
  : SCREEN_WIDTH(_SCREEN_WIDTH)
  , SCREEN_HEIGHT(_SCREEN_HEIGHT)
{
  this->window =
    SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

  this->screen = SDL_GetWindowSurface(this->window);
  this->playerScoreRect = { int(SCREEN_WIDTH * X_PLAYER_SCORE_OFFSET),
                            int(SCREEN_HEIGHT * Y_SCORE_OFFSET), 0, 0 };
  this->botScoreRect = { int(SCREEN_WIDTH * X_BOT_SCORE_OFFSET),
                         int(SCREEN_HEIGHT * Y_SCORE_OFFSET), 0, 0 };
  this->dividingStripRect = { SCREEN_WIDTH / 2, 0, 0, 0 };
}

void Window::SetDividingStripXOffset(int offset)
{
  dividingStripRect = { SCREEN_WIDTH / 2 - offset, 0, 0, 0 };
}
