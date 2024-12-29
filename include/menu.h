#pragma once
#include <raylib.h>
#include <vector>
#include <string>


class Menu
{
public:
  Menu();
  void Update();
  void Draw();
private:
  // Menu items and state
  std::vector<std::string> mainMenuItems;
  std::vector<std::vector<std::string>> subMenuItems;
  int currentMenu;
  std::vector<std::string> GetCurrentMenu();
  int selectedIndex;
  int fontSize;
  int spacing;
  int startX;
  int startY;
};

