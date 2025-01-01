#include "../include/hit.h"

Texture2D Hit::image = {0};

Hit::Hit(Vector2 position)
{
  shouldDelete = false;
  if(image.id == 0)
    image = LoadTexture("assets/sprites/effects/hit.png");
  this->position = position;
  sourceImage = {0, 0, (float)image.width / 4, (float)image.height};
  frame = 0;
  frameTimer = 0.0;
}

void Hit::Update(float deltaTime)
{
  if (frameTimer > 0)
    {
      frameTimer -= deltaTime;
    }
  else
    {
      if (frame >= 3)
        shouldDelete = true;
      else
        frame++;

      sourceImage.x = frame * image.width / 4;
      frameTimer = 0.02;
    }
}

void Hit::Draw()
{
  DrawTextureRec(image, sourceImage, position, WHITE);
}

void Hit::UnloadImages()
{
  UnloadTexture(image);
}

bool Hit::ShouldDelete()
{
  if (shouldDelete)
    return true;
  else
    return false;
}
