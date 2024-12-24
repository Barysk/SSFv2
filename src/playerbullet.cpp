#include "../include/playerbullet.h"
#include <iostream>

Texture2D PlayerBullet::image = {0};

PlayerBullet::PlayerBullet(Vector2 position, Vector2 direction)
{
  // Loading image if not loaded yet
  if(image.id == 0)
   image = LoadTexture("assets/sprites/player/playerBullet.png");
  this->position = position;
  this->direction = direction;

  // Normalizing Vector2: Vector2 length is needed
  float magnitude = sqrt((this->direction.x * this->direction.x) +
                         (this->direction.y * this->direction.y));

  // Normalizing Vector2: so the movement dioganally is not faster
  if (magnitude != 0)
  {
    this->direction.x = this->direction.x / magnitude;
    this->direction.y = this->direction.y / magnitude;
  }

  speed = 150;
  timeActive = 0.0f;
  timeToLive = 1.2f;
  rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90;

}

void PlayerBullet::UnloadImage()
{
  UnloadTexture(image);
}

void PlayerBullet::Move(float deltaTime)
{
  timeActive += deltaTime; // Increment the time active
  position += direction * speed * deltaTime;
}

void PlayerBullet::Draw()
{

  //DrawCircle(position.x, position.y, 2.0f, WHITE);

  // Define the source rectangle (entire texture)
  Rectangle sRect = {0, 0, (float)image.width, (float)image.height};

  // Define the destination rectangle (where the texture will be drawn)
  Rectangle dRect = {position.x, position.y, (float)image.width, (float)image.height};

  // Set the origin of rotation (center of the texture)
  Vector2 origin = {image.width / 2.0f, image.height / 2.0f};

  // Draw the texture with rotation
  DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}

// Check if the bullet should be removed (after 1.5 seconds)
bool PlayerBullet::ShouldDelete()
  {
    return timeActive >= timeToLive;
  }

