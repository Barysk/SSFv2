#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "../include/enemybullet.h"

class Enemy
{
public:
  static Texture2D images[5];
  Enemy(Vector2 position, int type);
  static void UnloadImages();
  void Move(float deltaTime, Vector2 playerPosition);
  void Draw();
  void Attack();
  Vector2 GetCollisionPosition();
  float GetCollisionRadius();
  std::vector<EnemyBullet> bullets;
  int type;
private:
  Vector2 position;
  Vector2 direction;
  float directionOffset;
  bool incrementDirectionOffset;
  int playerDistance;
  float lastTimeFired;
  float cooldown;
  int speed;
  int bulletSpeed;
  int bulletRotation;
  float rotation;

};


