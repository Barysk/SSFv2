#pragma once
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include "../include/playerbullet.h"

class Player
{
public:
  Player();
  ~Player();
  Camera2D camera;
  void Draw();
  void Move(float deltaTime, Vector2 direction);
  void Rotate(float degree);
  void Attack();
  Texture2D image;
  Vector2 position;
  Vector2 direction;
  std::vector<PlayerBullet> bullets;
private:
  float rotation;
  float lastTimeFired;
  int speed;
  int health;
  float cooldown;
  int cameraSpeed;
};

