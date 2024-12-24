#include "../include/playerbullet.h"
#include <iostream>


PlayerBullet::PlayerBullet(Vector2 position, Vector2 direction)
{
  // Loading image if not loaded yet
  if(image.id == 0)
    image = LoadTexture("assets/sprites/player/playerBullet.png");

  this->position = position;
  this->direction = direction;

  speed = 50;
  rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90;

}

void PlayerBullet::UnloadImage()
{
  UnloadTexture(image);
}

void PlayerBullet::Move(float deltaTime)
{
  position += direction * speed * deltaTime;
  std::cout << "X: " << position.x << "Y: " << position.y << std::endl;
}

void PlayerBullet::Draw()
{
  DrawCircle(position.x, position.y, 3.0f, WHITE);

  // Define the source rectangle (entire texture)
  // Rectangle sRect = {0, 0, (float)image.width, (float)image.height};

  // // Define the destination rectangle (where the texture will be drawn)
  // Rectangle dRect = {position.x, position.y, (float)image.width*2, (float)image.height*2};

  // // Set the origin of rotation (center of the texture)
  // Vector2 origin = {image.width / 2.0f, image.height / 2.0f};

  // // Draw the texture with rotation
  // DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}

