#pragma once
#include "GameModel.h"
#include "Window.h"

class SurfaceStorage;
class View
{
public:
  static void Draw(GameModel& gameModel, Window& window,
                   SurfaceStorage& surfaceStorage);

private:
  static void DrawScore(GameModel& gameModel, Window& window,
                        SurfaceStorage& surfaceStorage);
};