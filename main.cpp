#include <raylib.h>
#include "include/game.h"


#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int main(void)
{

  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;
  bool isFullscreen = false;

  // Enable config flags for resizable window and vertical synchro
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SSFv2");
  SetWindowMinSize(640, 480);

  int gameScreenWidth = 640;
  int gameScreenHeight = 480;

  // Render texture initialization, used to hold the rendering result so we can easily resize it
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use

  SetTargetFPS(144);

  Game game;

  while (!WindowShouldClose())
    {

      // Compute required framebuffer scaling
      float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);

      // Handle fullscreen toggle
      // I will now assume that it is going to work on windows machines. Will check later.
      // But this situation shows that probably other library is worth considering.
      if (IsKeyPressed(KEY_F11))
      {
          isFullscreen = !isFullscreen;

          if (isFullscreen)
              SetWindowState(FLAG_WINDOW_MAXIMIZED && FLAG_WINDOW_TOPMOST && FLAG_BORDERLESS_WINDOWED_MODE);
          else
              ClearWindowState(FLAG_WINDOW_MAXIMIZED && FLAG_WINDOW_TOPMOST && FLAG_BORDERLESS_WINDOWED_MODE);
      }

      //game.HandleInput();
      game.Update();

      // Draw everything in the render texture, note this will not be rendered on screen, yet
      BeginTextureMode(target);
        ClearBackground(BLACK);
        game.Draw();
      EndTextureMode();


      BeginDrawing();
        ClearBackground(BLACK);     // Clear screen background

        // Draw render texture to screen, properly scaled
        // DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
        Rectangle sRect = {0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height};
        Rectangle dRect = {(GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f,
                            (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                            (float)gameScreenWidth*scale, (float)gameScreenHeight*scale};
        DrawTexturePro(target.texture, sRect, dRect, (Vector2){0, 0}, 0.0f, WHITE);
      EndDrawing();

    }

  CloseWindow();

  return 0;
}
