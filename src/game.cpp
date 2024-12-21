#include "../include/game.h"


Game::Game()
{

}

Game::~Game()
{

}

void Game::Update()
{

}

void Game::Draw()
{
  player.Draw();
}

void Game::HandleInput()
{

  // TODO there is no chanse now for them to work together - meaning I if I press W and S, I'll get:
  // X: 1 Y: 0
  // X: 0 Y: 1
  // X: 1 Y: 0
  // X: 0 Y: 1
  // ifs are separate to work on each direction movement at the same time
  if(IsKeyDown(KEY_A))
    {
      player.Move({-1, 0});
    }
  if(IsKeyDown(KEY_D))
    {
      player.Move({1, 0});
    }
  if(IsKeyDown(KEY_W))
    {
      player.Move({0, -1});
    }
  if(IsKeyDown(KEY_S))
    {
      player.Move({0, 1});
    }
  if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D))
    {
      player.Move({0, 0});
    }
}
