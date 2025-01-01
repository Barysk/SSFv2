#include "../include/enemy.h"

Texture2D Enemy::images[5] = {0};

Enemy::Enemy(Vector2 position, int type)
{

  if(images[type -1].id == 0)
    {
      switch (type)
        {
        case 1:
          images[0] = LoadTexture("assets/sprites/enemy/enemy_1.png");
          break;
        case 2:
          images[1] = LoadTexture("assets/sprites/enemy/enemy_2.png");
          break;
        case 3:
          images[2] = LoadTexture("assets/sprites/enemy/enemy_3.png");
          break;
        case 4:
          images[3] = LoadTexture("assets/sprites/enemy/enemy_4.png");
          break;
        case 5:
          images[4] = LoadTexture("assets/sprites/enemy/enemy_5.png");
          break;
        default:
          break;
        }
    }

  this->position = position;
  this->type = type;
  speed = GetRandomValue(105, 115);
  bulletSpeed = speed/1.5+10;
  direction = {0, 0};
  rotation = 0.0;
  lastTimeFired = 0.0f;
  playerDistance = GetRandomValue(75, 100);

  switch (this->type) {
    case 1:
      cooldown = 0.32f;
      break;
    case 2:
      cooldown = 0.64f;
      break;
    case 3:
      cooldown = 0.32f;
      break;
    case 4:
      cooldown = 0.16f;
      if(GetRandomValue(0, 1) == 1)
        {
          directionOffset = 35.0f;
          incrementDirectionOffset = false;
        }
      else
        {
          directionOffset = -35.0f;
          incrementDirectionOffset = true;
        }
      break;
    case 5:
      cooldown = 0.32f;
      directionOffset = 0.0f;
      incrementDirectionOffset = (bool)GetRandomValue(0,1);
      playerDistance += 20;
      bulletRotation = GetRandomValue(-1, 1);
      break;
    default:
      cooldown = 1.0f;;
    }

}

void Enemy::UnloadImages()
{
  for(int i = 0; i < 4; i++)
    {
      UnloadTexture(images[i]);
    }
}

void Enemy::Move(float deltaTime, Vector2 playerPosition)
{

    // Direction to player
    direction = { playerPosition.x - position.x, playerPosition.y - position.y };

    // Distance between player and enemy
    distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    // If the enemy is closer than playerDistance, move away
    if (distance < playerDistance)
      {
        if (speed > -10) speed -= 10;
      }
    else if(distance <= playerDistance + 30 && distance >= playerDistance)
      {
        if (speed > 0) speed -= 1;
        if (speed < 0) speed += 1;
      }
    else
      {
        if (speed < 110) speed += 5;
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

    position.x += direction.x * (float)speed * deltaTime;
    position.y += direction.y * (float)speed * deltaTime;
}


void Enemy::Draw()
{
  Rectangle sRect = {0, 0, (float)images[type-1].width, (float)images[type-1].height};
  Rectangle dRect = {position.x, position.y, (float)images[type-1].width, (float)images[type-1].height};
  Vector2 origin = { images[type-1].width / 2.0f, images[type-1].height / 2.0f };
  DrawTexturePro(images[type-1], sRect, dRect, origin, rotation, WHITE);

  // Hurtbox
  //DrawCircleV(position, 4, BLUE);
  //DrawCircleV(position, 3, WHITE);
}

void Enemy::Attack(std::vector<EnemyBullet>& bullets)
{
  switch (type) {
    case 1:
      if(GetTime() - lastTimeFired >= cooldown)
        {
          for(int i = -1; i <= 1; i += 1)
            {
              bullets.push_back(EnemyBullet(position, Vector2Rotate(direction, i * DEG2RAD), speed/2 + (float)bulletSpeed, 0, type));
            }
          lastTimeFired = GetTime();
        }
      break;
    case 2:
      if(GetTime() - lastTimeFired >= cooldown)
        {
          for(int i = -16; i <= 16; i += 4)
            {
              bullets.push_back(EnemyBullet(position, Vector2Rotate(direction, i * DEG2RAD), speed/2 + (float)bulletSpeed, 0, type));
            }
          lastTimeFired = GetTime();
        }
      break;
    case 3:
      if(GetTime() - lastTimeFired >= cooldown)
        {
          bullets.push_back(EnemyBullet(position, Vector2Rotate(direction, (float)GetRandomValue(-30, 30) * DEG2RAD), (float)bulletSpeed, 0, type));
          lastTimeFired = GetTime();
        }
    case 4:
      if(GetTime() - lastTimeFired >= cooldown)
        {
          if(incrementDirectionOffset)
            {
              directionOffset += 5;
              if(directionOffset >= 35)
                incrementDirectionOffset = false;
            }
          else
            {
              directionOffset -= 5;
              if(directionOffset <= -35)
                incrementDirectionOffset = true;
            }

          for(int i = -25; i <= 25; i += 50)
            {
              bullets.push_back(EnemyBullet(position, Vector2Rotate(direction, (i + directionOffset) * DEG2RAD), speed/2 + (float)bulletSpeed, 0, type));
            }
          lastTimeFired = GetTime();
        }
    case 5:
      if(GetTime() - lastTimeFired >= cooldown && (speed >= -64 && speed <= 64))
        {
          if(incrementDirectionOffset)
            {
              directionOffset += 15;
              if(directionOffset >= 45)
                directionOffset = 0;
            }
          else
            {
              directionOffset -= 15;
              if(directionOffset <= -45)
                directionOffset = 0;
            }
          for(int i = 0; i < 360; i += 45)
            {
              bullets.push_back(EnemyBullet(position, Vector2Rotate(direction, (i + directionOffset) * DEG2RAD), (float)bulletSpeed / 2, bulletRotation, type));
            }
          lastTimeFired = GetTime();
        }
    default:
      break;
    }
}

Vector2 Enemy::GetCollisionPosition()
{
  return position;
}

float Enemy::GetCollisionRadius()
{
  return 3.0f;
}

int Enemy::GetScore()
{
  switch (type) {
    case 1:
      return 100 + 10000 / distance;
      break;
    case 2:
      return 200 + 20000 / distance;
      break;
    case 3:
      return 300 + 30000 / distance;
      break;
    case 4:
      return 400 + 40000 / distance;
      break;
    case 5:
      return 500 + 50000 / distance;
      break;
    default:
      return 0;
    }
}
