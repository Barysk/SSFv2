#pragma once
#include <raylib.h>

class Player
{
public:
  Player();
  ~Player();
  Camera2D camera;
  void Draw();
  void Update();
  void Move(Vector2 direction);
  void Rotate(float degree);
  void Attack();

private:
  Vector2 position;
  Vector2 direction;
  Texture2D image;
  float rotation;
  int speed;
  int health;


};

