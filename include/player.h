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
  void Draw();
  void Move(float deltaTime, Vector2 direction);
  void Rotate(float degree);
  void Attack(Vector2 attackDirection, std::vector<PlayerBullet>& bullets);
  void SetHealth(int value);
  int GetHealth();
  void DealDamage(int value);
  Vector2 GetCollisionPosition();
  float GetCollisionRadius();
  Camera2D camera;
  //std::vector<PlayerBullet> bullets;
  Texture2D image;
  Vector2 position;

private:
  Vector2 direction;
  float rotation;
  float lastTimeFired;
  int speed;
  int health;
  float cooldown;
  int cameraSpeed;
};

