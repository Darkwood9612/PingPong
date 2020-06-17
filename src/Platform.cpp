#include "Platform.h"
#include <SDL2\SDL_rect.h>

Platform::Platform()
{
}

int Platform::GetPosX()
{
	return this->rect.x;
}

int Platform::GetPosY()
{
	return this->rect.y;
}

void Platform::SetPosX(int newValue)
{
	this->rect.x = newValue;
}

void Platform::SetPosY(int newValue)
{
	this->rect.y = newValue;;
}
