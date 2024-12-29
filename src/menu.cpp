#include "../include/menu.h"


Menu::Menu()
{
  gameState = 0;

  // MainMenu items
  mainMenu = {"Start Game", "Tutorial", "Exit"};
  selectedIndex = 0;
  fontSize = 32;
  spacing = 32;
  startX = 16;
  startY = 16*3;

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
          gameState = 2;
          break;
        case 2:
          gameState = 3;
          break;
        default:
          break;
        }
    }
}

void Menu::Draw()
{
  for (int i = 0; i < mainMenu.size(); i++)
    {
      DrawText(mainMenu[i].c_str(), startX, startY + i * spacing, fontSize, (i == selectedIndex) ? GREEN : WHITE);
    }
}

int Menu::GetGameState()
{
  return gameState;
}
