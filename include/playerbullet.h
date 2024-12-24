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
private:
  Vector2 position;
  Vector2 direction;
  float timeActive;
  float timeToLive;
  float rotation;
  float speed;
};

