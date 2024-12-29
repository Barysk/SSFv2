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
  int GetGameState();
private:
  // Menu items and state
  std::vector<std::string> mainMenu;
  int gameState;
  int selectedIndex;
  int fontSize;
  int spacing;
  int startX;
  int startY;
};

