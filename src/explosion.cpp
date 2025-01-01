#include "../include/explosion.h"

Texture2D Explosion::image = {0};

Explosion::Explosion(Vector2 position)
{
  shouldDelete = false;
  if(image.id == 0)
    image = LoadTexture("assets/sprites/effects/explosion.png");
  this->position = position;
  sourceImage = {0, 0, (float)image.width / 8, (float)image.height};
  frame = 0;
  frameTimer = 0.0;
}

void Explosion::Update(float deltaTime)
{
  if (frameTimer > 0)
    {
      frameTimer -= deltaTime;
    }
  else
    {
      if (frame >= 7)
        shouldDelete = true;
      else
        frame++;

      sourceImage.x = frame * image.width / 8;
      frameTimer = 0.02;
    }
}

void Explosion::Draw()
{
  DrawTextureRec(image, sourceImage, position, WHITE);
}

void Explosion::UnloadImages()
{
  UnloadTexture(image);
}

bool Explosion::ShouldDelete()
{
  if (shouldDelete)
    return true;
  else
    return false;
}
