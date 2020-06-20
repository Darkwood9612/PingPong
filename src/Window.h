#pragma once
#include <SDL2\SDL_video.h>

class Window
{
public:
  Window(const char* title, uint32_t windowFlags = SDL_WINDOW_SHOWN,
         const int _SCREEN_WIDTH = 640, const int _SCREEN_HEIGHT = 480);

  SDL_Surface* screen = nullptr;
  SDL_Window* window = nullptr;
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  int windowPlayerScore = -1;
  int windowBotScore = -1;

  SDL_Rect GetPlayerScoreRect() { return playerScoreRect; };
  SDL_Rect GetBotScoreRect() { return botScoreRect; };

  SDL_Rect GetDividingStripRect() { return dividingStripRect; };
  void SetDividingStripXOffset(int offset);

private:
  const float X_PLAYER_SCORE_OFFSET = 0.4;
  const float X_BOT_SCORE_OFFSET = 0.6;
  const float Y_SCORE_OFFSET = 0.06;

  SDL_Rect dividingStripRect;
  SDL_Rect playerScoreRect;
  SDL_Rect botScoreRect;
};