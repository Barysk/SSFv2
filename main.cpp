#include "raylib.h"
#include "include/game.h"

int main(void)
{

  const int screenWidth = 640;
  const int screenHeight = 480;

  InitWindow(screenWidth, screenHeight, "SSFv2");

  SetWindowState(FLAG_WINDOW_RESIZABLE);

  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose())
    {

      game.HandleInput();

      BeginDrawing();
      ClearBackground(BLACK);

      game.Draw();

      EndDrawing();

    }


    CloseWindow();

    return 0;
}
