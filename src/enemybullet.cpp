#include "../include/enemybullet.h"

Texture2D EnemyBullet::image = {0};

EnemyBullet::EnemyBullet(Vector2 position, Vector2 direction)
{
  if(image.id == 0)
    image = LoadTexture("assets/sprites/enemy/enemyBullet_1.png");
  this->position = position;
  this->direction = direction;

  float magnitude = sqrt((this->direction.x * this->direction.x) +
                         (this->direction.y * this->direction.y));

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

void EnemyBullet::UnloadImage()
{
  UnloadTexture(image);
}

void EnemyBullet::Move(float deltaTime, int enemyType)
{
  timeActive += deltaTime; // Increment the time active
  position += direction * speed * deltaTime;
}

void EnemyBullet::Draw()
{

  //DrawCircle(position.x, position.y, 2.0f, WHITE);

  Rectangle sRect = {0, 0, (float)image.width, (float)image.height};
  Rectangle dRect = {position.x, position.y, (float)image.width, (float)image.height};
  Vector2 origin = {image.width / 2.0f, image.height / 2.0f};
  DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}

// Check if the bullet should be removed (after 1.5 seconds)
bool EnemyBullet::ShouldDelete()
{
  return timeActive >= timeToLive;
}
