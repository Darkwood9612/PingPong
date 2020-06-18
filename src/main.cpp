#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Windows.h>

#include "SurfaceStorage.h"
#include "GameModel.h"
#include "Controller.h"
#include "View.h"

#include <stdexcept>
#include <algorithm>

#undef main 

namespace {
    constexpr char* PLATFORM_BACKGROUND_PATH = "bmp/platform.bmp";
    constexpr char* SIVIDING_STRIP_BACKGROUND_PATH = "bmp/dividingStrip.bmp";
    constexpr char* BALL_BACKGROUND_PATH = "bmp/ball.bmp";
    
    constexpr char* FONT_PATH = "font/fast99.ttf";
    constexpr int FONT_SIZE = 36;

    constexpr char* WINDOW_TITLE = "PingPong";
}

int Quit(SDL_Window* window, SurfaceStorage& surfaceStorage) {

    surfaceStorage.FreeAllSurfaces();
    window ? SDL_DestroyWindow(window) : throw std::runtime_error("window == nullptr");
    SDL_Quit();
    return 0;
}

int main(int argc, char** args) {
    
    //while (!IsDebuggerPresent()) {
    //    Sleep(1);
    //}
    
    try{
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("Fatal initialization SDL error!");

        if (TTF_Init() != 0)
            throw std::runtime_error("Fatal initialization TTF error!");
        
        
        SurfaceStorage surfaceStorage = SurfaceStorage(FONT_PATH, FONT_SIZE);
        Controller controller = Controller();
        View view = View();

        Window windowModel = Window(WINDOW_TITLE, SDL_WINDOW_SHOWN, 1024, 768);
        if (!windowModel.window)
            throw std::runtime_error("window == nullptr");
        
        GameModel gameModel = GameModel(windowModel, surfaceStorage.LoadBMP("platform", PLATFORM_BACKGROUND_PATH));
        gameModel.dividingStrip = surfaceStorage.LoadBMP("dividingStrip", SIVIDING_STRIP_BACKGROUND_PATH);
        gameModel.ball = Ball({},surfaceStorage.LoadBMP("ball", BALL_BACKGROUND_PATH));

        while (true) {
            controller.UpdateModel(gameModel);
            view.Draw(gameModel, windowModel, surfaceStorage);
            
            if (gameModel.needCloseGame)
                break;
        }

        return Quit(windowModel.window, surfaceStorage);
    }
    catch (const std::exception& e){
        MessageBox(NULL, e.what(), NULL, MB_OK);
    }
};