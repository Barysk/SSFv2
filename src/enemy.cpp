#include "../include/enemy.h"

Texture2D Enemy::image = {0};

Enemy::Enemy()
{
  if(image.id == 0)
    image = LoadTexture("assets/sprites/enemy/enemy.png");
 // this->position = position;
  position = {200,200};
  speed = 110;
  direction = {0, 0};
  rotation = 0.0;
  playerDistance = 75.0f;
}

void Enemy::UnloadImages()
{
  UnloadTexture(image);
}

void Enemy::Move(float deltaTime, Vector2 playerPosition)
{

    // Direction to player
    direction = { playerPosition.x - position.x, playerPosition.y - position.y };

    // Distance between player and enemy
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    // If the enemy is closer than playerDistance, move away
    if (distance < playerDistance)
      {
        if (speed > -10)
          speed -= 10;
      }
    else if(distance <= playerDistance + 10 && distance >= playerDistance - 10)
      {
        if (speed > 0)
          speed -= 5;
      }
    else
      {
        if (speed < 110)
          speed += 5;
      }

    // Normalizing vector
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
      {
        direction.x /= magnitude;
        direction.y /= magnitude;
      }

    if (magnitude != 0)
      {
        rotation = atan2(direction.y, direction.x) * RAD2DEG + 90; // Convert radians to degrees
      }

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
}


void Enemy::Draw()
{
  Rectangle sRect = {0, 0, (float)image.width, (float)image.height};
  Rectangle dRect = {position.x, position.y, (float)image.width, (float)image.height};
  Vector2 origin = { image.width / 2.0f, image.height / 2.0f };
  DrawTexturePro(image, sRect, dRect, origin, rotation, WHITE);
}
