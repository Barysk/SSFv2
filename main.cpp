#include <raylib.h>
#include "include/game.h"
#include "include/menu.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int main(void)
{
  //Music Soundtrack = LoadMusicStream("assets/sounds/UnknownSpace");

  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;
  bool isFullscreen = false;
  bool isGamePaused = false; // for handling pause
  int gameState = 0; // for handling transitions [Will be rethinked]
  // 0: Main Menu,
  // 1: Game is running
  // 2: End screen
  // 3: Must Close

  float scale;

  // Enable config flags for resizable window and vertical synchro
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SSFv2");
  SetWindowMinSize(640, 480);

  InitAudioDevice();

  int gameScreenWidth = 640;
  int gameScreenHeight = 480;

  // Render texture initialization, used to hold the rendering result so we can easily resize it
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use

  SetTargetFPS(60);

  Menu menu;
  Game game;
  Rectangle sRect;
  Rectangle dRect;

  while (!WindowShouldClose() && gameState != 3)
    {

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

      // change framerate
      if (IsKeyPressed(KEY_THREE))
        SetTargetFPS(30);
      else if (IsKeyPressed(KEY_SIX))
          SetTargetFPS(60);
      else if (IsKeyPressed(KEY_TWO))
          SetTargetFPS(120);
      else if (IsKeyPressed(KEY_FOUR))
          SetTargetFPS(144);

      // Handle Mute
      if (IsKeyPressed(KEY_M) && GetMasterVolume() != 0)
        SetMasterVolume(0.0f);
      else if (IsKeyPressed(KEY_M) && GetMasterVolume() == 0)
        SetMasterVolume(100.0f);

      // Compute required framebuffer scaling
      scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);


      // Game states
      switch (gameState) {
        case 0: // Main Menu

          menu.Update();

          BeginTextureMode(target);
            ClearBackground(BLACK);
            menu.Draw();
            gameState = menu.GetGameState();
            DrawText(Game::FormatWithLeadingZeros(Game::LoadHiScore(),8).c_str(), 16*15 , 16, 32, GRAY);
          EndTextureMode();

          break;
        case 1:
          // Handle Pause
          if(IsKeyPressed(KEY_SPACE) && isGamePaused)
            isGamePaused = false;
          else if(IsKeyPressed(KEY_SPACE) && !isGamePaused)
            isGamePaused = true;

          if(!isGamePaused)
            {
              game.Update();
              game.CheckForCollisions();
            }

          if(game.ShouldEnd())
            gameState = 2;

          // Draw everything in the render texture, note this will not be rendered on screen, yet
          BeginTextureMode(target);
            ClearBackground(BLACK);
            game.Draw();
            if(isGamePaused)
              DrawText("Paused", (gameScreenWidth / 2) - 64, 16, 32, WHITE);
          EndTextureMode();
          break;
        case 2:
          if (IsKeyPressed(KEY_ENTER))
            {
              game.RESET();
              menu.RESET();
              gameState = 0;
            }

          BeginTextureMode(target);
            ClearBackground(BLACK);

            DrawText("CONNECTION LOST", 16, 16, 32, RED);

            DrawText("HIGHEST SCORE IS: ", 16, 16*4, 32, WHITE);
            DrawText(Game::FormatWithLeadingZeros(Game::LoadHiScore(),8).c_str(), 16*22, 16*4, 32, WHITE);

            DrawText("YOUR SCORE IS: ", 16, 16*6, 32, WHITE);
            DrawText(Game::FormatWithLeadingZeros(game.GetScore(),8).c_str(), 16*22, 16*6, 32, WHITE);

            DrawText("PRESS ENTER TO RESUME.", 16, 16*8, 32, WHITE);
          EndTextureMode();

          break;
        default:
          break;
        }


      BeginDrawing();
        ClearBackground(BLACK);     // Clear screen background

        // Draw render texture to screen, properly scaled
        // DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
        sRect = {0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height};
        dRect = {(GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f,
                            (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                            (float)gameScreenWidth*scale, (float)gameScreenHeight*scale};
        DrawTexturePro(target.texture, sRect, dRect, (Vector2){0, 0}, 0.0f, (isGamePaused) ? GREEN : WHITE);
      EndDrawing();

    }


  CloseAudioDevice();

  CloseWindow();

  return 0;
}
