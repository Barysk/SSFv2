#pragma once
#include "../include/player.h"
#include "../include/background.h"
#include "../include/enemy.h"

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
  Enemy enemy;
  Vector2 playerDirection;
  Vector2 playerAttackDirection;
  Background background;
};

