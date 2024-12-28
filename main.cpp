#include <raylib.h>
#include <string>
#include "include/game.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int main(void)
{
  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;
  bool isFullscreen = false;

  float scale;

  // Enable config flags for resizable window and vertical synchro
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SSFv2");
  SetWindowMinSize(640, 480);

  int gameScreenWidth = 640;
  int gameScreenHeight = 480;

  // Render texture initialization, used to hold the rendering result so we can easily resize it
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use

  SetTargetFPS(60);

  // Menu items and state
  std::vector<std::string> menuItems = {"Start Game", "Options", "Brief", "Exit"};
  int selectedIndex = 0;
  const int fontSize = 20;
  const int spacing = 30;
  const int startX = 10;
  const int startY = GetScreenHeight() / 2 - (menuItems.size() * spacing / 2);
  bool isGamePaused = false; // for handling pause
  int gameState = 0;
  // 0: Main Menu,
  // 1: Game is running
  // 2: Options are opened
  // 3: Brief is running
  // 4: Must Close

  Game game;
  Rectangle sRect;
  Rectangle dRect;

  while (!WindowShouldClose())
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

      // Compute required framebuffer scaling
      scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);


      // Game states
      switch (gameState) {
        case 0: // Main Menu
          // Handle Main Menu Input
          if (IsKeyPressed(KEY_UP))
            {
              selectedIndex--;
              if (selectedIndex < 0) selectedIndex = menuItems.size() - 1; // Wrap around
            }
          else if (IsKeyPressed(KEY_DOWN))
            {
              selectedIndex++;
              if (selectedIndex >= menuItems.size()) selectedIndex = 0; // Wrap around
            }

          // Handle selection
          if (IsKeyPressed(KEY_ENTER))
            {
              switch (selectedIndex)
                {
                  case 0: /* Start Game Logic */ break;
                  case 1: /* Options Logic */ break;
                  case 2: /* Brief Logic */ break;
                  case 3: CloseWindow(); break;
                }
            }

          BeginTextureMode(target);
            ClearBackground(BLACK);



            for (size_t i = 0; i < menuItems.size(); i++) {
                Color color = (i == selectedIndex) ? YELLOW : WHITE;
                DrawText(menuItems[i].c_str(), startX, startY + i * spacing, fontSize, color);
            }
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

          // Draw everything in the render texture, note this will not be rendered on screen, yet
          BeginTextureMode(target);
            ClearBackground(BLACK);
            game.Draw();
          EndTextureMode();
          break;
        case 2:

          break;
        case 3:

          break;
        case 4:

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
        DrawTexturePro(target.texture, sRect, dRect, (Vector2){0, 0}, 0.0f, (isGamePaused) ? DARKGREEN : WHITE);
      EndDrawing();

    }

  CloseWindow();

  return 0;
}
