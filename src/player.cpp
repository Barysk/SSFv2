#include "../include/player.h"
#include <iostream>

Player::Player()
{
  image = LoadTexture("assets/sprites/player/pTest.png");
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.width)/2;
  rotation = 0.0f;
  speed = 100;
  health = 3;
  lastTimeFired = 0.0f;
  cooldown = 0.15f;

  // Camera Init
  camera = {0}; // reseting any settings
  camera.target = { (GetScreenWidth() - image.width) / 2.0f, (GetScreenHeight() - image.height) / 2.0f }; // initial camera pos
  camera.offset = { (GetScreenWidth() - image.width) / 2.0f, (GetScreenHeight() - image.height) / 2.0f }; // centering camera on player
  camera.zoom = 2.0f; // camera's zoom
  camera.rotation = 0; // rotation
  cameraSpeed = 40;
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


void Player::Move(float deltaTime, Vector2 direction)
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

void Player::Attack(Vector2 attackDirection)
{
  if(attackDirection.x != 0 || attackDirection.y != 0)
    {
    rotation = atan2(attackDirection.y, attackDirection.x) * RAD2DEG + 90;

    if(GetTime() - lastTimeFired >= cooldown)
      {
        bullets.push_back(PlayerBullet(position, attackDirection));
        lastTimeFired = GetTime();
      }
    }
}
