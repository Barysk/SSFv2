#pragma once
#include <raylib.h>
#include <raymath.h>


class PlayerBullet
{
public:
  static Texture2D image;
  PlayerBullet(Vector2 position, Vector2 direction);
  static void UnloadImage();
  void Move(float deltaTime);
  void Draw();
  bool ShouldDelete();
  Vector2 GetCollisionPosition();
  void Penetrate();
  float GetCollisionRadius();
  bool shouldBeDestroyed;
private:
  Vector2 position;
  Vector2 direction;
  int penetrationStrength;
  float timeActive;
  float timeToLive;
  float rotation;
  float speed;
};

