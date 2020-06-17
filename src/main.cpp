#include <SDL2/SDL.h>
#include "SurfaceStorage.h"
#include <Windows.h>
#include <stdexcept>
#include <algorithm>
#include "GameModel.h"
#include "Controller.h"
#include "View.h"
#include <SDL2/SDL_ttf.h>

#undef main 

int Init(const char* title, SDL_Window* window, SDL_Surface* scr, int SCREEN_WIDTH, int SCREEN_HEIGHT, uint32_t flags) {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("Fatal initialization error!");

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    
    if (!window)
        throw std::runtime_error("window == nullptr");

    scr = SDL_GetWindowSurface(window);

    return 0;
}

int Quit(SDL_Window* window, SurfaceStorage& surfaceStorage) {

    surfaceStorage.FreeAllSurfaces();
    window ? SDL_DestroyWindow(window) : throw std::runtime_error("window == nullptr");
    SDL_Quit();
    return 0;
}

int main(int argc, char** args) {
    
    ///while (!IsDebuggerPresent()) {
    ///    Sleep(1);
    ///}

    try{
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("Fatal initialization error!");
        
        SurfaceStorage surfaceStorage;
        Controller controller = Controller();
        View view = View();

        WindowModel windowModel = WindowModel("PingPong");
        if (!windowModel.window)
            throw std::runtime_error("window == nullptr");
        
        GameModel gameModel = GameModel(windowModel, surfaceStorage.LoadBMP("platform", "platform.bmp"));
        gameModel.dividingStrip = surfaceStorage.LoadBMP("dividingStrip", "dividingStrip.bmp");

        while (true) {
            controller.UpdateModel(gameModel);
            view.Draw(gameModel, windowModel);
            
            if (gameModel.needCloseGame)
                break;
        }

        return Quit(windowModel.window, surfaceStorage);
    }
    catch (const std::exception& e){
        MessageBox(NULL, e.what(), NULL, MB_OK);
    }
};