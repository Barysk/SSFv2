#pragma once
#include <raylib.h>
#include <raymath.h>


class PlayerBullet
{
public:
  Texture2D image;
  PlayerBullet(Vector2 position, Vector2 direction, float speed);
  void Update();
  void Draw();
  bool isOnScreen;
private:
  Vector2 position;
  Vector2 direction;
  float rotation;
  float speed;
};

