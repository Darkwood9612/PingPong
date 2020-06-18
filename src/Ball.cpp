#include "Ball.h"

Ball::Ball(SDL_Rect _rect, SDL_Surface* _background)
{
	this->rect = _rect;
	this->background = _background;
}

SDL_Rect Ball::GetRect()
{
	return rect;
}

SDL_Surface Ball::GetBackGround()
{
	return background ? *background : SDL_Surface();
}

void Ball::Respawn()
{
}
