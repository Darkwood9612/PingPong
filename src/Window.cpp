#include "Window.h"

WindowModel::WindowModel()
{
	this->window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	this->screen = SDL_GetWindowSurface(this->window);
}

WindowModel::WindowModel(const char* title, uint32_t windowFlags, const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT) :
	SCREEN_WIDTH(_SCREEN_WIDTH), SCREEN_HEIGHT(_SCREEN_HEIGHT) {
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	this->screen = SDL_GetWindowSurface(this->window);
}
