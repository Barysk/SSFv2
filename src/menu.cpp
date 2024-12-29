#include "../include/menu.h"


Menu::Menu()
{
  // MainMenu items
  mainMenuItems = {"Start Game", "Tutorial", "Scores", "Settings", "Exit"};
  selectedIndex = 0;
  fontSize = 20;
  spacing = 30;
  startX = 10;
  startY = 10;

  currentMenu = 0;
  // 0 - Main
  // 1 - StartGame
  // 2 - Scores
  // 3 - Settings


  subMenuItems =
    {
      {"Easy", "Medium", "Hard", "Insane"}, // Start Game submenu
      {"Record 1", "Record 2", "Record 3"}, // Scores submenu
      {"Max FPS", "Fullscreen", "Vsync"}    // Settings submenu
    };

}

void Menu::Update()
{
  const std::vector<std::string>& menuItems = GetCurrentMenu();

  // Navigation for the current menu
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
      if (currentMenu == 0)
        {
          // Main menu selection logic
          switch (selectedIndex)
            {
              case 0: currentMenu = 1; break; // Start Game submenu
              case 1: /* Tutorial logic */ break;               // No submenu
              case 2: currentMenu = 2; break;    // Scores submenu
              case 3: currentMenu = 3; break;  // Settings submenu
              case 4: CloseWindow(); break;                      // Exit
            }
        }
      else
        {
          // Submenu logic (return to Main menu or perform specific actions)
          currentMenu = 0; // Return to main menu after selection
        }
    }

  // Return to main menu with Backspace
  if (IsKeyPressed(KEY_BACKSPACE) && currentMenu != 0)
    {
      currentMenu = 0;
    }
}

void Menu::Draw()
{
  const std::vector<std::string>& menuItems = GetCurrentMenu();

      // Draw the main menu, grayed out if a submenu is active
      for (size_t i = 0; i < mainMenuItems.size(); i++)
        {
          Color color = (currentMenu != 0) ? GRAY : WHITE;
          if (i == selectedIndex && currentMenu == 0)
            {
              color = GREEN; // Highlight only if Main menu is active
            }
          DrawText(mainMenuItems[i].c_str(), startX, startY + i * spacing, fontSize, color);
        }

      // Draw the current submenu, if active
      if (currentMenu != 0)
        {
          const int submenuStartX = startX + 200; // Position submenu to the right of the main menu
          for (size_t i = 0; i < menuItems.size(); i++)
            {
              Color color = (i == selectedIndex) ? GREEN : WHITE;
              DrawText(menuItems[i].c_str(), submenuStartX, startY + i * spacing, fontSize, color);
            }
        }
}

std::vector<std::string> Menu::GetCurrentMenu()
{
  switch (currentMenu)
    {
      case 0: return mainMenuItems;
      case 1: return subMenuItems[0];
      case 2: return subMenuItems[1];
      case 3: return subMenuItems[2];
      default: return {}; // Return an empty vector for unsupported states
    }
}
