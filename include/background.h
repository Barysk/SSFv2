#pragma once
#include <raylib.h>

class Background
{
public:
  Background();
  ~Background();
  void Update();
  void Draw();
private:
  void drawBackground(Texture2D& image);
  Texture2D background;
  Texture2D midground;
  Texture2D foreground;
  float offsetBack;
  float offsetMid;
  float offsetFor;
};

