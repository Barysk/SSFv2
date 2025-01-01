#pragma once
#include <raylib.h>


class Hit
{
public:
  Hit(Vector2 position);
  static Texture2D image;
  void Update(float deltaTime);
  void Draw();
  static void UnloadImages();
  bool ShouldDelete();
private:
  bool shouldDelete;
  float frameTimer;
  Vector2 position;
  Rectangle sourceImage;
  int frame;
};
