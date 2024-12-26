#pragma once
#include <raylib.h>
#include <raymath.h>

class Enemy
{
public:
  static Texture2D image;
  Enemy(Vector2 position, int type);
  static void UnloadImages();
  void Move(float deltaTime, Vector2 playerPosition);
  void Draw();
private:
  Vector2 position;
  Vector2 direction;
  int playerDistance;
  float speed;
  float rotation;
  int type; // there will be 5 different
};


