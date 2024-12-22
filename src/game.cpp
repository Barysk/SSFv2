#include "../include/game.h"


Game::Game()
{
  playerDirection = {0, 0};
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

  if(IsKeyDown(KEY_A))
    {
      playerDirection.x += -1;
    }
  if(IsKeyDown(KEY_D))
    {
      playerDirection.x += 1;
    }
  if(IsKeyDown(KEY_W))
    {
      playerDirection.y += -1;
    }
  if(IsKeyDown(KEY_S))
    {
      playerDirection.y += 1;
    }

  // Function to move player
  player.Move(playerDirection);

  playerDirection = {0, 0};

}
