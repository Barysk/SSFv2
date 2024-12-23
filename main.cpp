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
  SetWindowMinSize(320, 240);

  int gameScreenWidth = 640;
  int gameScreenHeight = 480;

  // Render texture initialization, used to hold the rendering result so we can easily resize it
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use

  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose())
    {

      // Compute required framebuffer scaling
      float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);


      // Handle fullscreen toggle
      if (IsKeyPressed(KEY_F11))
      {
          isFullscreen = !isFullscreen;

          if (isFullscreen)
          {
              SetWindowState(FLAG_FULLSCREEN_MODE);
          }
          else
          {
              ClearWindowState(FLAG_FULLSCREEN_MODE);
          }
      }

      game.HandleInput();
      game.Update();

      // Draw everything in the render texture, note this will not be rendered on screen, yet
      BeginTextureMode(target);
        ClearBackground(BLACK);
        game.Draw();
      EndTextureMode();


      BeginDrawing();
        ClearBackground(BLACK);     // Clear screen background

        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                       (Rectangle){ (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                       (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
      EndDrawing();

      // BeginDrawing();
      // ClearBackground(BLACK);

      // game.Draw();

      // EndDrawing();

    }

  CloseWindow();

  return 0;
}
