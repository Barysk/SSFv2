#pragma once
#include <raylib.h>
#include <raymath.h>

class Enemy
{
public:
  static Texture2D image;
  Enemy();
  static void UnloadImages();
  void Move(float deltaTime, Vector2 playerPosition);
  void Draw();
private:
  Vector2 position;
  Vector2 direction;
  float playerDistance;
  int speed;
  float rotation;
};


