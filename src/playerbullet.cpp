#include "../include/playerbullet.h"


PlayerBullet::PlayerBullet(Vector2 position, Vector2 direction, float speed)
{
  if(image.id == 0)
    image = LoadTexture("../assets/sprites/player/playerBullet.png");

  this->position = position;
  this->direction = direction;
  this->speed = speed;
  rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90;
  isOnScreen = true;
}



void PlayerBullet::Update()
{
  position += direction * speed;
}

void PlayerBullet::Draw()
{
  // Define the source rectangle (entire texture) *Consider later usage of static_cast<float>
  Rectangle sRect = {0, 0, (float)image.width, (float)image.height};

  // Define the destination rectangle (where the texture will be drawn)
  Rectangle dRect = {position.x, position.y, (float)image.width, (float)image.height};

  // Set the origin of rotation (center of the texture)
  Vector2 origin = {image.width / 2.0f, image.height / 2.0f};

  // Draw the texture with rotation
  DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}

