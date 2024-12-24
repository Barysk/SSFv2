#include "../include/game.h"


Game::Game()
{
  playerDirection = {0, 0};
  deltaTime = 0.0f;
}

Game::~Game()
{
  background.UnloadImages();
}

void Game::Update()
{
  // Updating deltaTime
  deltaTime = GetFrameTime();

  // Input
  HandleInput();

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
  //DrawText("Use WASD to move", 10, 10, 20, DARKGRAY);
  //DrawText("Use WASD to move", 10, 30, 20, DARKGRAY);

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
  player.Move(playerDirection, deltaTime);
  // Function to move background
  background.Move(playerDirection, deltaTime);
  // Resetting Direction
  playerDirection = {0, 0};

}
