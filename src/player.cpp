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
  if (direction.x == 0 && direction.y == 0)
    {
      this->direction = {0, 0};
    }
  else
    {
      this->direction.x += direction.x;
      this->direction.y += direction.y;
    }

  // Check for overload on X
  if(this->direction.x > 1)
    this->direction.x = 1;
  else if(this->direction.x < -1)
    this->direction.x = -1;

  // Check for overload on Y
  if(this->direction.y > 1)
    this->direction.y = 1;
  else if(this->direction.y < -1)
    this->direction.y = -1;

  // Normalizing Vector2
  if(this->direction.x != 0 && this->direction.y != 0)
    {

      float magnitude = sqrt((this->direction.x * this->direction.x) +
                             (this->direction.y * this->direction.y));

      if (magnitude != 0) // Avoid division by zero
      {
        this->direction.x /= magnitude;
        this->direction.y /= magnitude;
      }
    }

  // Moving player
  position.x += direction.x * speed;
  position.y += direction.y * speed;

}

void Update();
void Attack();
