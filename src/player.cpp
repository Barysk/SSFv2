#include "../include/player.h"
#include <raymath.h>


Player::Player()
{
  image = LoadTexture("assets/sprites/player/pTest.png");
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.width)/2;
  rotation = 0;
  speed = 5;
}

Player::~Player()
{
  UnloadTexture(image);
}

void Player::Draw()
{
  // Define the source rectangle (entire texture) *Consider later usage of static_cast<float>
  Rectangle sRect = {0, 0, (float)image.width, (float)image.height};

  // Define the destination rectangle (where the texture will be drawn)
  Rectangle dRect = {position.x, position.y, (float)image.width, (float)image.height};

  // Set the origin of rotation (center of the texture)
  Vector2 origin = { image.width / 2.0f, image.height / 2.0f };

  // Draw the texture with rotation
  DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}


void Player::Move(Vector2 direction)
{

  this->direction.x = direction.x;
  this->direction.y = direction.y;


  // Normalizing Vector2: Vector2 length is needed
  float magnitude = sqrt((this->direction.x * this->direction.x) +
                         (this->direction.y * this->direction.y));

  // Normalizing Vector2: so the movement dioganally is not faster
  if (magnitude != 0)
  {
    this->direction.x = this->direction.x / magnitude;
    this->direction.y = this->direction.y / magnitude;
  }

  // Moving player
  position.x += this->direction.x * speed;
  position.y += this->direction.y * speed;

  if (magnitude != 0)
    {
      rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90; // Convert radians to degrees
    }

}

void Update();
void Attack();
