#pragma once
#include "../include/player.h"
#include "../include/background.h"


class Game
{
public:
  Game();
  ~Game();
  void Update();
  void Draw();
  void HandleInput();
private:
  float deltaTime;
  Player player;
  Vector2 playerDirection;
  Background background;
};

