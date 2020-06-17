#pragma once
#include "GameModel.h"
#include "Window.h"

class SurfaceStorage;
class View
{
public:
	View(void);

	void Draw(GameModel& gameModel, WindowModel& windowModel, SurfaceStorage& surfaceStorage);

private:
	void DrawScore(GameModel& gameModel, WindowModel& windowModel, SurfaceStorage& surfaceStorage);
};