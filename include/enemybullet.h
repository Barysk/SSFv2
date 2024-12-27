#pragma once
#include <raylib.h>
#include <raymath.h>

class EnemyBullet
{
public:
  static Texture2D images[5];
  EnemyBullet(Vector2 position, Vector2 direction, float speed, int bulletRotation, int type);
  static void UnloadImage();
  void Move(float deltaTime);
  void Draw();
  bool ShouldDelete();
  bool shouldBeDestroyed;
  Vector2 GetCollisionPosition();
  float GetCollisionRadius();
  int type;
private:
  Vector2 position;
  Vector2 direction;
  float timeActive;
  float timeToLive;
  int bulletRotation;
  int rotationOffset;
  float rotation;
  float speed;
};

