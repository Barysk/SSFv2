#pragma once
#include "../include/player.h"


class Game
{
public:
  Game();
  ~Game();
  void Update();
  void Draw();
  void HandleInput();
private:
  Player player;
};

