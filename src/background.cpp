#include "../include/background.h"

Background::Background()
{
  background = LoadTexture("assets/sprites/space/background.png");
  midground = LoadTexture("assets/sprites/space/farStars.png");
  foreground = LoadTexture("assets/sprites/space/nearStars.png");
  offsetBack = 0.0f;
  offsetMid = 0.0f;
  offsetFor = 0.0f;
}

Background::~Background()
{
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
}

void Background::Update()
{
  offsetBack -= 0.1f;
  offsetMid -= 0.5f;
  offsetFor -= 1.0f;

  if (offsetBack <= -background.width*2) offsetBack = 0;
  if (offsetMid <= -midground.width*2) offsetMid = 0;
  if (offsetFor <= -foreground.width*2) offsetFor = 0;
}

void Background::drawBackground(Texture2D& image)
{
  // Center
  DrawTextureEx(image, {(float)GetScreenHeight()/2, (float)GetScreenHeight()/2}, 0.0, 10.0f, WHITE); // center
  DrawTextureEx(image, {(float)GetScreenHeight()/2 + image.width*10, (float)GetScreenHeight()/2}, 0.0, 10.0f, WHITE); // right
  DrawTextureEx(image, {(float)GetScreenHeight()/2 - image.width*10, (float)GetScreenHeight()/2}, 0.0, 10.0f, WHITE); // left
  // Top
  DrawTextureEx(image, {(float)GetScreenHeight()/2, (float)GetScreenHeight()/2 - image.height*10}, 0.0, 10.0f, WHITE); // center
  DrawTextureEx(image, {(float)GetScreenHeight()/2 + image.width*10, (float)GetScreenHeight()/2 - image.height*10}, 0.0, 10.0f, WHITE); // right
  DrawTextureEx(image, {(float)GetScreenHeight()/2 - image.width*10, (float)GetScreenHeight()/2 - image.height*10}, 0.0, 10.0f, WHITE); // left
  // Bottom
  DrawTextureEx(image, {(float)GetScreenHeight()/2, (float)GetScreenHeight()/2 + image.height*10}, 0.0, 10.0f, WHITE); // center
  DrawTextureEx(image, {(float)GetScreenHeight()/2 + image.width*10, (float)GetScreenHeight()/2 + image.height*10}, 0.0, 10.0f, WHITE); // right
  DrawTextureEx(image, {(float)GetScreenHeight()/2 - image.width*10, (float)GetScreenHeight()/2 + image.height*10}, 0.0, 10.0f, WHITE); // left
}

void Background::Draw()
{

  drawBackground(background);
  drawBackground(midground);
  drawBackground(foreground);

}
