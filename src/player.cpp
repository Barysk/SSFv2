#include "../include/player.h"

Texture2D Player::images[3] = {0};

Player::Player()
{
  health = 3;
  for(int i = 0; i < 3; i++)
    {
      if(images[i].id == 0)
        {
          switch (i)
            {
            case 0:
              images[0] = LoadTexture("assets/sprites/player/playerMin.png");
              break;
            case 1:
              images[1] = LoadTexture("assets/sprites/player/playerMid.png");
              break;
            case 2:
              images[2] = LoadTexture("assets/sprites/player/playerMax.png");
              break;
            default:
              break;
            }
        }
    }

  position.x = (GetScreenWidth() - images[health-1].width)/2;
  position.y = (GetScreenHeight() - images[health-1].width)/2;
  rotation = 0.0f;
  speed = 100;
  lastTimeFired = 0.0f;
  cooldown = 0.16f;

  // Camera Init
  camera = {0}; // reseting any settings
  camera.target = { (GetScreenWidth() - images[health-1].width) / 2.0f, (GetScreenHeight() - images[health-1].height) / 2.0f }; // initial camera pos
  camera.offset = { (GetScreenWidth() - images[health-1].width) / 2.0f, (GetScreenHeight() - images[health-1].height) / 2.0f }; // centering camera on player
  camera.zoom = 2.0f; // camera's zoom
  camera.rotation = 0; // rotation
  cameraSpeed = 40;
}

Player::~Player()
{
  for(int i = 0; i < 3; i++)
    {
      UnloadTexture(images[i]);
    }
}

void Player::Draw()
{
  if (health > 0)
    {
      // Define the source rectangle (entire texture) *Consider later usage of static_cast<float>
      Rectangle sRect = {0, 0, (float)images[health-1].width, (float)images[health-1].height};

      // Define the destination rectangle (where the texture will be drawn)
      Rectangle dRect = {position.x, position.y, (float)images[health-1].width, (float)images[health-1].height};

      // Set the origin of rotation (center of the texture)
      Vector2 origin = { images[health-1].width / 2.0f, images[health-1].height / 2.0f };

      // Draw the texture with rotation
      DrawTexturePro(images[health-1], sRect, dRect, origin, rotation, WHITE);
    }
}


void Player::Move(float deltaTime, Vector2 direction)
{
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

  // Moving player
  position.x += this->direction.x * speed * deltaTime;
  position.y += this->direction.y * speed * deltaTime;

  if (magnitude != 0)
    {
      rotation = atan2(this->direction.y, this->direction.x) * RAD2DEG + 90; // Convert radians to degrees
    }

  // Move camera
  camera.target.x += (position.x - camera.target.x) * 0.25f * deltaTime * cameraSpeed;
  camera.target.y += (position.y - camera.target.y) * 0.25f * deltaTime * cameraSpeed;
}

void Player::Attack(Vector2 attackDirection, std::vector<PlayerBullet>& bullets)
{
  if(attackDirection.x != 0 || attackDirection.y != 0)
    {
    rotation = atan2(attackDirection.y, attackDirection.x) * RAD2DEG + 90;

    if(GetTime() - lastTimeFired >= cooldown)
      {
        bullets.push_back(PlayerBullet(position, Vector2Rotate(attackDirection, GetRandomValue(-16, 16) * DEG2RAD)));
        lastTimeFired = GetTime();
      }
    }
}

void Player::SetHealth(int value)
{
  health = value;
}

int Player::GetHealth()
{
  return health;
}

void Player::DealDamage(int value)
{
  health -= value;
  if(health < 0)
    health = 0;
}

Vector2 Player::GetCollisionPosition()
{
  return position;
}

float Player::GetCollisionRadius()
{
  return 1.0f;
}
