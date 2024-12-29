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
  std::vector<std::string> mainMenu;
  int currentMenu;
  int selectedIndex;
  std::vector<std::vector<std::string>> optionMenu;
  int subSelectedIndexX;
  int subSelectedIndexY;
  int fontSize;
  int spacing;
  int startX;
  int startY;
};

