#include "../include/enemybullet.h"

Texture2D EnemyBullet::images[5] = {0};

EnemyBullet::EnemyBullet(Vector2 position, Vector2 direction, float speed, int bulletRotation, int type)
{
  if(images[type -1].id == 0)
    {
      switch (type)
        {
        case 1:
          images[0] = LoadTexture("assets/sprites/enemy/enemyBullet_1.png");
          break;
        case 2:
          images[1] = LoadTexture("assets/sprites/enemy/enemyBullet_2.png");
          break;
        case 3:
          images[2] = LoadTexture("assets/sprites/enemy/enemyBullet_3.png");
          break;
        case 4:
          images[3] = LoadTexture("assets/sprites/enemy/enemyBullet_4.png");
          break;
        case 5:
          images[4] = LoadTexture("assets/sprites/enemy/enemyBullet_5.png");
          break;
        default:
          break;
        }
    }

  this->type = type;
  shouldBeDestroyed = false;
  //if(image.id == 0)
  //  image = LoadTexture("assets/sprites/enemy/enemyBullet_1.png");
  this->position = position;
  this->direction = direction;

  float magnitude = sqrt((this->direction.x * this->direction.x) +
                         (this->direction.y * this->direction.y));

  if (magnitude != 0)
  {
    this->direction.x = this->direction.x / magnitude;
    this->direction.y = this->direction.y / magnitude;
  }

  this->bulletRotation = bulletRotation;
  rotationOffset = 0;

  this->speed = speed;
  timeActive = 0.0f;
  timeToLive = 6.4f;
  rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90;
}

void EnemyBullet::UnloadImage()
{
  for(int i = 0; i < 4; i++)
    {
      UnloadTexture(images[i]);
    }
}

void EnemyBullet::Move(float deltaTime)
{
  if(bulletRotation == 0)
    {
      timeActive += deltaTime; // Increment the time active
      position += direction * speed * deltaTime;
    }
  else if (bulletRotation > 0)
    {
      timeActive += deltaTime;
      position += Vector2Rotate(direction, (float)rotationOffset * DEG2RAD) * speed * deltaTime;
      if(rotationOffset < 90)
        rotationOffset += 1;
      else
        bulletRotation = -1;
    }
  else if (bulletRotation < 0)
    {
      timeActive += deltaTime;
      position += Vector2Rotate(direction, (float)rotationOffset * DEG2RAD) * speed * deltaTime;
      if(rotationOffset > -90)
        rotationOffset -= 1;
      else
        bulletRotation = 1;
    }

}

void EnemyBullet::Draw()
{
  Rectangle sRect = {0, 0, (float)images[type-1].width, (float)images[type-1].height};
  Rectangle dRect = {position.x, position.y, (float)images[type-1].width, (float)images[type-1].height};
  Vector2 origin = {images[type-1].width / 2.0f, images[type-1].height / 2.0f};
  DrawTexturePro(images[type-1], sRect, dRect, origin, 0.0f, WHITE);

  // Hurtbox/Hitbox
  // DrawCircleV(position, 2, BLUE);
  // DrawCircleV(position, 1, WHITE);
}

// Check if the bullet should be removed (after 1.5 seconds)
bool EnemyBullet::ShouldDelete()
{
  if(timeActive >= timeToLive || shouldBeDestroyed)
    return true;
  else
    return false;
}

Vector2 EnemyBullet::GetCollisionPosition()
{
  return position;
}

float EnemyBullet::GetCollisionRadius()
{
  return 1.0f;
}
