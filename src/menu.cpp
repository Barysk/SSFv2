#include "../include/menu.h"


Menu::Menu()
{
  // MainMenu items
  mainMenu = {"Start Game", "Tutorial", "Scores", "Settings", "Exit"};
  selectedIndex = 0;
  subSelectedIndexX = 0;
  subSelectedIndexY = 0;
  fontSize = 20;
  spacing = 30;
  startX = 10;
  startY = 10;

  currentMenu = 0;
  // 0 - Main
  // 1 - Settings
  // 2 - Scores



  optionMenu =
  {
    {"FPS", "SOUND", "MODE", "VSYNC", "RESET", "BACK"},
    {"60", "120", "144", "240"},
    {"ON", "OFF"},
    {"WINDOWED", "MAXIMIZED"},
    {"ON", "OFF"},
  };

  // subMenuItems =
  //   {
  //     {"Record 1", "Record 2", "Record 3", "Back"}, // Scores submenu
  //     {"Max FPS", "Fullscreen", "Vsync", "Back"}    // Settings submenu
  //   };

}

void Menu::Update()
{
  switch (currentMenu) {
    case 0:
      if (IsKeyPressed(KEY_UP))
        {
          selectedIndex--;
          if (selectedIndex < 0) selectedIndex = mainMenu.size() - 1;
        }
      else if (IsKeyPressed(KEY_DOWN))
        {
          selectedIndex++;
          if (selectedIndex >= mainMenu.size()) selectedIndex = 0;
        }

      if (IsKeyPressed(KEY_ENTER))
        {
          switch (selectedIndex) {
            case 0:
              // start game
              break;
            case 1:
              // start tutor
              break;
            case 2:
              // scores
              break;
            case 3:
              currentMenu = 1;
              break;
            case 4:
              // Exit
              CloseWindow();
              break;
            default:
              break;
            }
        }
      break;

    case 1:
      if (IsKeyPressed(KEY_UP))
        {
          subSelectedIndexY--;
          if (subSelectedIndexY < 0) subSelectedIndexY = optionMenu[0].size() - 1;
        }
      else if (IsKeyPressed(KEY_DOWN))
        {
          subSelectedIndexY++;
          if (subSelectedIndexY >= optionMenu[0].size()) subSelectedIndexY = 0;
        }

      if (IsKeyPressed(KEY_BACKSPACE))
        currentMenu = 0;

      if (IsKeyPressed(KEY_ENTER))
        {
          switch (subSelectedIndexY) {
            case 0:
              // start game
              break;
            case 1:
              // start tutor
              break;
            case 2:
              // scores
              break;
            case 3:

              break;
            case 4:

              break;
            case 5:
              currentMenu = 0;
              break;
            default:
              break;
            }
        }
      break;

      break;

    default:
      break;
    }


}

void Menu::Draw()
{
  switch (currentMenu) {
    case 0: // Draw Main Menu
      for (int i = 0; i < mainMenu.size(); i++)
        {
          DrawText(mainMenu[i].c_str(), startX, startY + i * spacing, fontSize, (i == selectedIndex) ? GREEN : WHITE);
        }
      break;

    case 1: // Draw Main Menu Darkened and Opened SubMenu
      for (int i = 0; i < mainMenu.size(); i++)
        {
          DrawText(mainMenu[i].c_str(), startX, startY + i * spacing, fontSize, (i == selectedIndex) ? DARKGREEN : DARKGRAY);
        }
      for (int i = 0; i < optionMenu[0].size(); i++)
        {
          DrawText(optionMenu[0][i].c_str(), startX+128, startY + i * spacing, fontSize, (i == subSelectedIndexY) ? GREEN : WHITE);
        }


      for (int i = 0; i < optionMenu[1].size(); i++)
        {
          DrawText(optionMenu[1][i].c_str(), startX+256 + i * spacing * 2, startY, fontSize, (i == subSelectedIndexX) ? GREEN : WHITE);
        }

      for (int i = 0; i < optionMenu[2].size(); i++)
        {
          DrawText(optionMenu[2][i].c_str(), startX+256 + i * spacing * 2, startY + spacing, fontSize, (i == subSelectedIndexX) ? GREEN : WHITE);
        }

      for (int i = 0; i < optionMenu[3].size(); i++)
        {
          DrawText(optionMenu[3][i].c_str(), startX+256 + i * spacing * 4, startY + spacing * 2, fontSize, (i == subSelectedIndexX) ? GREEN : WHITE);
        }

      for (int i = 0; i < optionMenu[4].size(); i++)
        {
          DrawText(optionMenu[4][i].c_str(), startX+256 + i * spacing * 2, startY + spacing * 3, fontSize, (i == subSelectedIndexX) ? GREEN : WHITE);
        }

      break;
    default:
      break;
    }
}
