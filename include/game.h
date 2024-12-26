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
  //void SpawnEnemies(int type1, int type2, int type3, int type4, int type5);
  void SpawnEnemies(int type, int number);
private:
  float spawnRadius;
  float deltaTime;
  Player player;
  std::vector<Enemy> enemies;
  Vector2 playerDirection;
  Vector2 playerAttackDirection;
  Background background;
};

