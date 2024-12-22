#include "../include/player.h"
#include <raymath.h>
#include <iostream>


Player::Player()
{
  image = LoadTexture("assets/sprites/player/pTest.png");
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.width)/2;
  speed = 10;
}

Player::~Player()
{
  UnloadTexture(image);
}

void Player::Draw()
{
  DrawTextureV(image, position, WHITE);
}


void Player::Move(Vector2 direction)
{

  this->direction.x = direction.x;
  this->direction.y = direction.y;

  // Normalizing Vector two, so the movement dioganally is not faster
  float magnitude = sqrt((this->direction.x * this->direction.x) +
                         (this->direction.y * this->direction.y));

  if (magnitude != 0)
  {
    this->direction.x = this->direction.x / magnitude;
    this->direction.y = this->direction.y / magnitude;
  }

  // Moving player
  position.x += this->direction.x * speed;
  position.y += this->direction.y * speed;

}

void Update();
void Attack();
