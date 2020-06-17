#include <SDL2/SDL.h>
#include "SurfaceStorage.h"
#include <Windows.h>
#include <stdexcept>
#include <algorithm>
#include "GameModel.h"
#include "Controller.h"
#include "View.h"
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

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    uint32_t windowFlags = SDL_WINDOW_SHOWN;
    
    ///while (!IsDebuggerPresent()) {
    ///    Sleep(1);
    ///}

    try{
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("Fatal initialization error!");
        
        SurfaceStorage surfaceStorage;
        Controller controller = Controller();
        View view = View();

        GameModel model = GameModel(SCREEN_WIDTH, SCREEN_HEIGHT, surfaceStorage.LoadBMP("platform", "Platform.bmp", 10 , 80));
        model.window = SDL_CreateWindow("PingPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
        model.screen = SDL_GetWindowSurface(model.window);

        if (!model.window)
            throw std::runtime_error("window == nullptr");

        while (true) {
            controller.UpdateModel(model);
            view.Draw(model);
            
            if (model.needExitGame)
                break;
        }

        return Quit(model.window, surfaceStorage);
    }
    catch (const std::exception& e){
        MessageBox(NULL, e.what(), NULL, MB_OK);
    }
};