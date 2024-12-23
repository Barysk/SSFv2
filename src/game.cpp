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
  // Background
  background.Update();

  // Savepoint

  // Player

  // Enemy

}

void Game::Draw()
{
  // Background
  background.Draw();

  // Savepoint

  // Player
  BeginMode2D(player.camera);
  player.Draw();
  EndMode2D();
  DrawText("Use WASD to move", 10, 10, 20, DARKGRAY);

  // Enemy
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
  background.Move(playerDirection);
  playerDirection = {0, 0};

}
