#pragma once
#include "../include/player.h"
#include "../include/background.h"
#include "../include/enemy.h"
#include <string>

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
  static std::string FormatWithLeadingZeros(int number, int width);
  void UpdateHiScore();
  void SaveHiScore(int hiSocre);
  static int LoadHiScore();
  void RESET();
  bool ShouldEnd();
  int GetScore();
private:
  Sound playerShooting;
  Sound playerHit;
  Sound enemyExplosion;
  void SpawnWave();
  int currentWave;
  int maxSpawnToken;
  float midWaveTimer;
  float midWaveTime;
  float spawnRadius;
  float deltaTime;
  Player player;
  std::vector<PlayerBullet> playerBullets;
  std::vector<Enemy> enemies;
  std::vector<EnemyBullet> enemyBullets;
  Vector2 playerDirection;
  Vector2 playerAttackDirection;
  Background background;

  float invincibilityTime;
  float invincibilityTimer;

  int hiScore;
  int score;
};

