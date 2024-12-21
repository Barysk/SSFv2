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
