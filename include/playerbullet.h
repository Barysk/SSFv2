#pragma once
#include <raylib.h>
#include <raymath.h>


class PlayerBullet
{
public:
  Texture2D image;
  PlayerBullet(Vector2 position, Vector2 direction);
  void UnloadImage();
  void Move(float deltaTime);
  void Draw();
private:
  Vector2 position;
  Vector2 direction;
  float rotation;
  float speed;
};

