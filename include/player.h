#pragma once
#include <raylib.h>

class Player
{
public:
  Player();
  ~Player();
  void Draw();
  void Update();
  void Move(Vector2 direction);
  // void MoveRight();
  // void MoveLeft();
  // void MoveUp();
  // void MoveDown();
  void Attack();

private:
  Vector2 SumVector2(Vector2& a, Vector2& b);
  Texture2D image;
  Vector2 position;
  Vector2 direction;
  int speed;
  int health;


};

