#include "raylib.h"
#include "include/game.h"

int main(void)
{

  const int screenWidth = 640;
  const int screenHeight = 480;
  bool isFullscreen = false;


  InitWindow(screenWidth, screenHeight, "SSFv2");

  SetTargetFPS(60);

  Game game;



  while (!WindowShouldClose())
    {

      // Handle fullscreen toggle
      if (IsKeyPressed(KEY_F12))
      {
          isFullscreen = !isFullscreen;

          if (isFullscreen)
          {
              SetWindowState(FLAG_FULLSCREEN_MODE);
          }
          else
          {
              ClearWindowState(FLAG_FULLSCREEN_MODE);
              SetWindowSize(screenWidth, screenHeight);
          }
      }

      game.HandleInput();
      game.Update();

      BeginDrawing();
      ClearBackground(BLACK);

      game.Draw();

      EndDrawing();

    }


    CloseWindow();


    return 0;
}
