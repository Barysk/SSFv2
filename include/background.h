#pragma once
#include <raylib.h>
#include <raymath.h>

class Background
{
public:
  Background();
  void UnloadImages();
  void Update();
  void Draw();
  void Move(float deltaTime, Vector2 direction);
private:
  void drawBackground(Texture2D& image, Vector2 offset);
  Texture2D background;
  Texture2D midground;
  Texture2D foreground;
  Vector2 offset;
  float parallaxSpeed;
  float parallaxStrengthBack;
  float parallaxStrengthMid;
  float parallaxStrengthFor;
  Vector2 offsetBack;
  Vector2 offsetMid;
  Vector2 offsetFor;
};

