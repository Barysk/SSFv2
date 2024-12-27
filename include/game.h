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
  void SpawnEnemies(int type, int number);
  void CheckForCollisions();
private:
  float spawnRadius;
  float deltaTime;
  Player player;
  std::vector<PlayerBullet> playerBullets;
  std::vector<Enemy> enemies;
  std::vector<EnemyBullet> enemyBullets;
  Vector2 playerDirection;
  Vector2 playerAttackDirection;
  Background background;
};

