#include "../include/menu.h"


Menu::Menu()
{
  gameState = 0;

  // MainMenu items
  mainMenu = {"Start Game", "Exit"};
  selectedIndex = 0;
  fontSize = 32;
  spacing = 32;
  startX = 16;
  startY = 16;

}

void Menu::Update()
{
  if (IsKeyPressed(KEY_UP))
    {
      selectedIndex--;
      if (selectedIndex < 0) selectedIndex = mainMenu.size() - 1;
    }

  if (IsKeyPressed(KEY_DOWN))
    {
      selectedIndex++;
      if (selectedIndex >= mainMenu.size()) selectedIndex = 0;
    }

  if (IsKeyPressed(KEY_ENTER))
    {
      switch (selectedIndex) {
        case 0:
          gameState = 1;
          break;
        case 1:
          gameState = 3;
          break;
        default:
          break;
        }
    }
}

void Menu::Draw()
{
  int textPos = 120;
  Color textColour = DARKGRAY;

  for (int i = 0; i < mainMenu.size(); i++)
    {
      DrawText(mainMenu[i].c_str(), startX, startY + i * spacing, fontSize, (i == selectedIndex) ? GREEN : WHITE);
    }

  DrawText("CLUIvG [bkc]", 16, textPos, 20, textColour); textPos += 20;
  DrawText("------------", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Use Arrow Keys to attack in different directions", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Use WASD to move in different directions", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Press Space to pause/unpause the game", 16, textPos, 20, textColour); textPos += 20;
  DrawText("--------------------------------------", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Press ESC to exit the game at any moment", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Press F11 to toggle fullscreen mode", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Press M to mute/unmute sounds", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-Press 3, 6, 2, or 4 to set FPS to 30, 60, 120, or 144", 16, textPos, 20, textColour); textPos += 20;
  DrawText("------------------------------------------------------", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-The numbers you see here are your highest score", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-The health of your ship is indicated by its color", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-In the game, you'll see a wave indicator, score,", 16, textPos, 20, textColour); textPos += 20;
  DrawText(" and high score", 16, textPos, 20, textColour); textPos += 20;
  DrawText("---------------", 16, textPos, 20, textColour); textPos += 20;
  DrawText("-There are some hidden mechanics that", 16, textPos, 20, textColour); textPos += 20;
  DrawText("you will discover yourself", 16, textPos, 20, textColour);

}

int Menu::GetGameState()
{
  return gameState;
}

void Menu::RESET()
{
  gameState = 0;
  selectedIndex = 0;
}
