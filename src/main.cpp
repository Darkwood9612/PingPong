#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Windows.h>

#include "SurfaceStorage.h"
#include "GameModel.h"
#include "Controller.h"
#include "View.h"

#include <stdexcept>
#include <algorithm>
#include <filesystem>

#undef main 

namespace {
    constexpr char* PLATFORM_BACKGROUND_PATH = "image/platform.bmp";
    constexpr char* SIVIDING_STRIP_BACKGROUND_PATH = "image/dividingStrip.bmp";
    constexpr char* BALL_BACKGROUND_PATH = "image/ball.bmp";

    constexpr char* SOUND_WALL_COLLISION_PATH = "sound/wall—ollision.wav";
    constexpr char* SOUND_PLATFORM_COLLISION_PATH = "sound/platform—ollision.wav";
    constexpr char* SOUND_DEFEAT_PATH = "sound/defeat.wav";

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

    std::string tmp;
    auto getAbsoluatePath = [&](const char* relativePath) {
        tmp = (std::filesystem::path(args[0]).parent_path() / relativePath).string();
        return tmp.c_str();
    };

    try{
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("Fatal initialization SDL error!");

        if (TTF_Init() != 0)
            throw std::runtime_error("Fatal initialization TTF error!");
        
        
        SurfaceStorage surfaceStorage = SurfaceStorage(getAbsoluatePath(FONT_PATH), FONT_SIZE);
        Controller controller = Controller();
        View view = View();

        Window window = Window(WINDOW_TITLE, SDL_WINDOW_SHOWN, 1024, 768);
        if (!window.window)
            throw std::runtime_error("window == nullptr");
        
        GameModel gameModel = GameModel(window, surfaceStorage.LoadBMP("platform", getAbsoluatePath(PLATFORM_BACKGROUND_PATH)));
        gameModel.dividingStrip = surfaceStorage.LoadBMP("dividingStrip", getAbsoluatePath(SIVIDING_STRIP_BACKGROUND_PATH));
        gameModel.CreateBall(surfaceStorage.LoadBMP("ball", getAbsoluatePath(BALL_BACKGROUND_PATH)), gameModel.GetScreenCenter());

        while (true) {
            controller.UpdateModel(gameModel);
            view.Draw(gameModel, window, surfaceStorage);
            
            if (gameModel.needCloseGame)
                break;
        }

        return Quit(window.window, surfaceStorage);
    }
    catch (const std::exception& e){
        MessageBox(NULL, e.what(), NULL, MB_OK);
    }
};