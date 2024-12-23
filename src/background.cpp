#include "../include/background.h"


Background::Background()
{
  // background textures
  background = LoadTexture("assets/sprites/space/background.png");
  midground = LoadTexture("assets/sprites/space/farStars.png");
  foreground = LoadTexture("assets/sprites/space/nearStars.png");

  // parallax settings
  offset = {0, 0};
  parallaxStrengthBack = 0.1f;
  parallaxStrengthMid = 0.5f;
  parallaxStrengthFor = 0.9f;
  parallaxSpeed = 5.0f;
  offsetBack = {0, 0};
  offsetMid = {0, 0};
  offsetFor = {0, 0};
}



Background::~Background()
{
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
}

void Background::Update()
{
  // Update offsets with parallax and speed
  offsetBack += offset * parallaxStrengthBack * parallaxSpeed;
  offsetMid += offset * parallaxStrengthMid * parallaxSpeed;
  offsetFor += offset * parallaxStrengthFor * parallaxSpeed;

  // Wrap offsets for background
  if (offsetBack.x <= -background.width * 10 || offsetBack.x >= background.width * 10) offsetBack.x = 0;
  if (offsetBack.y <= -background.height * 10 || offsetBack.y >= background.height * 10) offsetBack.y = 0;

  // Wrap offsets for midground
  if (offsetMid.x <= -midground.width * 10 || offsetMid.x >= midground.width * 10) offsetMid.x = 0;
  if (offsetMid.y <= -midground.height * 10 || offsetMid.y >= midground.height * 10) offsetMid.y = 0;

  // Wrap offsets for foreground
  if (offsetFor.x <= -foreground.width * 10 || offsetFor.x >= foreground.width * 10) offsetFor.x = 0;
  if (offsetFor.y <= -foreground.height * 10 || offsetFor.y >= foreground.height * 10) offsetFor.y = 0;
}

void Background::Draw()
{

  drawBackground(background, offsetBack);
  drawBackground(midground, offsetMid);
  drawBackground(foreground, offsetFor);

}

void Background::Move(Vector2 direction)
{
  // Normalizing Vector2: Vector2 length is needed
  float magnitude = sqrt((direction.x * direction.x) +
                         (direction.y * direction.y));

  // Normalizing Vector2: so the movement dioganally is not faster
  if (magnitude != 0)
  {
    direction.x = direction.x / magnitude;
    direction.y = direction.y / magnitude;
  }

  // *make += to enable drift mode xD
  offset = direction;
}

void Background::drawBackground(Texture2D& image, Vector2 offset)
{
  float scale = 10.0f;
  float centerX = (float)GetScreenHeight() / 2 - offset.x;
  float centerY = (float)GetScreenHeight() / 2 - offset.y;

  for (int y = -2; y <= 2; y++)
  {
    for (int x = -2; x <= 2; x++)
    {
      float drawX = centerX + x * image.width * scale;
      float drawY = centerY + y * image.height * scale;
      DrawTextureEx(image, {drawX, drawY}, 0.0f, scale, WHITE);
    }
  }
}
