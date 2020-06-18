#pragma once
#include "GameModel.h"
#include "Window.h"

class SurfaceStorage;
class View
{
public:
	View();

	void Draw(GameModel& gameModel, Window& window, SurfaceStorage& surfaceStorage);

private:
	void DrawScore(GameModel& gameModel, Window& window, SurfaceStorage& surfaceStorage);
};