#pragma once
#include <raylib.h>
#include <raymath.h>

class EnemyBullet
{
public:
  static Texture2D image;
  EnemyBullet(Vector2 position, Vector2 direction);
  static void UnloadImage();
  void Move(float deltaTime, int enemyType);
  void Draw();
  bool ShouldDelete();
private:
  Vector2 position;
  Vector2 direction;
  float timeActive;
  float timeToLive;
  float rotation;
  float speed;
};

