#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <Windows.h>

#include "Controller.h"
#include "GameModel.h"
#include "SurfaceStorage.h"
#include "View.h"

#include "AudioStorage.h"
#include <filesystem>
#include <stdexcept>

#undef main

namespace {
constexpr char* PLATFORM_BACKGROUND_PATH = "image\\platform.bmp";
constexpr char* SIVIDING_STRIP_BACKGROUND_PATH = "image\\dividingStrip.bmp";
constexpr char* BALL_BACKGROUND_PATH = "image\\ball.bmp";

constexpr char* SOUND_COLLISION_WAV_PATH = "sound\\collision.wav";
constexpr char* BACKGROUND_MUSIC_PATH = "sound\\background_music.wav";
constexpr char* SOUND_RESPAWN_PATH = "sound\\respawn.wav";

constexpr int AUDIO_BUFFERS = 4096;

constexpr char* FONT_PATH = "font\\fast99.ttf";
constexpr int FONT_SIZE = 36;

constexpr char* WINDOW_TITLE = "PingPong";
}

int Quit(SDL_Window* window, SurfaceStorage& surfaceStorage,
         AudioStorage& audioStorage)
{

  surfaceStorage.FreeAllSurfaces();
  audioStorage.FreeAllMusic();
  audioStorage.FreeAllSoundEffect();

  window ? SDL_DestroyWindow(window)
         : throw std::runtime_error("window == nullptr");

  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}

int main(int argc, char** args)
{

  // while (!IsDebuggerPresent()) {
  //    Sleep(1);
  //}

  std::string tmp;
  auto getAbsoluatePath = [&](const char* relativePath) {
    tmp =
      (std::filesystem::path(args[0]).parent_path() / relativePath).string();
    return tmp.c_str();
  };

  srand(0);

  try {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      std::string err = SDL_GetError();
      throw std::runtime_error("Fatal initialization SDL error: " + err);
    }

    if (TTF_Init() != 0) {
      std::string err = TTF_GetError();
      throw std::runtime_error("Fatal initialization TTF error: " + err);
    }

    if (MIX_INIT_MID != Mix_Init(MIX_INIT_MID)) {
      std::string err = Mix_GetError();
      throw std::runtime_error("Could not initialize mixer Mix_Init: " + err);
    }

    SurfaceStorage surfaceStorage(getAbsoluatePath(FONT_PATH), FONT_SIZE);
    Controller controller;

    Window window = Window(WINDOW_TITLE, SDL_WINDOW_SHOWN, 1024, 768);
    if (!window.window)
      throw std::runtime_error("window == nullptr");

    GameModel gameModel =
      GameModel(window,
                surfaceStorage.LoadBMP(
                  "platform", getAbsoluatePath(PLATFORM_BACKGROUND_PATH)));

    gameModel.dividingStrip = surfaceStorage.LoadBMP(
      "dividingStrip", getAbsoluatePath(SIVIDING_STRIP_BACKGROUND_PATH));

    gameModel.CreateBall(
      surfaceStorage.LoadBMP("ball", getAbsoluatePath(BALL_BACKGROUND_PATH)),
      gameModel.GetScreenCenter());

    gameModel.audioStorage = AudioStorage(44100, MIX_DEFAULT_FORMAT,
                                          MIX_DEFAULT_CHANNELS, AUDIO_BUFFERS);

    gameModel.audioStorage.LoadSoundEffect(
      gameModel.audioStorage.collisionMusicName,
      getAbsoluatePath(SOUND_COLLISION_WAV_PATH));

    gameModel.audioStorage.LoadSoundEffect(
      gameModel.audioStorage.respawnMusicName,
      getAbsoluatePath(SOUND_RESPAWN_PATH));

    gameModel.audioStorage.LoadMusic(
      gameModel.audioStorage.backgroundMusicName,
      getAbsoluatePath(BACKGROUND_MUSIC_PATH));

    gameModel.audioStorage.PlayMusic(
      gameModel.audioStorage.backgroundMusicName, -1);

    while (true) {
      controller.UpdateModel(gameModel);
      View::Draw(gameModel, window, surfaceStorage);

      if (gameModel.needCloseGame)
        break;
    }

    return Quit(window.window, surfaceStorage, gameModel.audioStorage);
  } catch (const std::exception& e) {
    MessageBox(NULL, e.what(), NULL, MB_OK);
  }
};