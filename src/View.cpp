#include "View.h"
#include <sstream>
#include <string> 
#include <SDL2\SDL_ttf.h>
#include "SurfaceStorage.h"

View::View(void) {};

namespace {
    std::string IntToString(int n) {
        std::stringstream sstream;
        sstream << n;
        return sstream.str();
    }

    SDL_Surface* ScoreToSurface(const int FONT_SIZE, int number, const std::string& name, SurfaceStorage& surfaceStorage) {

        static TTF_Font* myFont = TTF_OpenFont("fast99.ttf", FONT_SIZE);
        SDL_Color myTextColor = { 255, 255, 255 };

        std::string score = IntToString(number);
        auto scoreImage = TTF_RenderText_Solid(myFont, score.c_str(), myTextColor);
        
        if (!scoreImage) {
            std::string err = TTF_GetError();
            throw std::runtime_error("Error in function 'TTF_RenderText_Solid': " + err);
        }

        surfaceStorage.SetBMP(name, scoreImage);
        return scoreImage;
    }

    SDL_Surface* GetOldScore(const std::string& name, SurfaceStorage& surfaceStorage) {
        return surfaceStorage.GetBMP(name);
    }
}

void View::DrawScore(GameModel& gameModel, WindowModel& windowModel, SurfaceStorage& surfaceStorage)
{
    static int oldPlayerScore = gameModel.GetPlayerScore() - 1;
    static int oldBotScore = gameModel.GetBotScore() - 1;
    static const int FONT_SIZE = 36;

    SDL_Rect rect;

    SDL_Surface* ScoreImage = gameModel.GetPlayerScore() != oldPlayerScore 
        ? ScoreToSurface(FONT_SIZE, gameModel.GetPlayerScore(), "playerScore", surfaceStorage)
        : GetOldScore("playerScore", surfaceStorage);
    
    oldPlayerScore = gameModel.GetPlayerScore();
    rect.x = int(windowModel.SCREEN_WIDTH * 0.4 - FONT_SIZE);
    rect.y = int(windowModel.SCREEN_HEIGHT * 0.06);
    SDL_BlitSurface(ScoreImage, NULL, windowModel.screen, &rect);

    ScoreImage = gameModel.GetBotScore() != oldBotScore 
        ? ScoreToSurface(FONT_SIZE, gameModel.GetBotScore(), "botScore", surfaceStorage)
        : GetOldScore("botScore", surfaceStorage);

    oldBotScore = gameModel.GetBotScore();
    rect.x = int(windowModel.SCREEN_WIDTH * 0.6);
    rect.y = int(windowModel.SCREEN_HEIGHT * 0.06);
    SDL_BlitSurface(ScoreImage, NULL, windowModel.screen, &rect);
}

void View::Draw(GameModel& gameModel, WindowModel& windowModel, SurfaceStorage& surfaceStorage)
{
    SDL_FillRect(windowModel.screen, NULL, SDL_MapRGB(windowModel.screen->format, 0, 0, 0));

    SDL_Surface platformBackground = gameModel.GetPlatformBackground();

    SDL_Rect playerRect = gameModel.GetPlayerRect();
    SDL_Rect botRect = gameModel.GetBotRect();

    auto infelicity = gameModel.dividingStrip ? gameModel.dividingStrip->w / 2 : 0;
    SDL_Rect centerRect = { int(windowModel.SCREEN_WIDTH / 2 - infelicity), 0, 0, 0};

    SDL_BlitSurface(gameModel.dividingStrip, NULL, windowModel.screen, &centerRect);
    SDL_BlitSurface(&platformBackground, NULL, windowModel.screen, &playerRect);
    SDL_BlitSurface(&platformBackground, NULL, windowModel.screen, &botRect);

    DrawScore(gameModel, windowModel, surfaceStorage);

    SDL_UpdateWindowSurface(windowModel.window);
}
