#include "../include/game.h"

Game::Game()
{
  playerDirection = {0, 0};
  playerAttackDirection = {0, 0};
  deltaTime = 0.0f;
}

Game::~Game()
{
  background.UnloadImages();
  PlayerBullet::UnloadImage();
  Enemy::UnloadImages();
}

void Game::Update()
{
  // Updating deltaTime
  deltaTime = GetFrameTime();

  // Player Input
  HandleInput();

  // delete inactive bullets
  for (auto it = player.bullets.begin(); it != player.bullets.end();)
  {
      // If the bullet's timeActive is >= 1.5 seconds, remove it
      if (it->ShouldDelete())
      {
          it = player.bullets.erase(it); // Erase the bullet and move to the next
      }
      else
      {
          ++it; // Otherwise, just move to the next bullet
      }
  }

  // Move active bullets
  for(auto& bullet: player.bullets)
    bullet.Move(deltaTime);

  // Background
  background.Update();

  // Savepoint

  // Enemy
  enemy.Move(deltaTime, player.position);

}

void Game::Draw()
{
  // Background
  background.Draw();

  // Savepoint

  // Player
  BeginMode2D(player.camera);

    // Drawing all the projectiles
    for(auto& bullet: player.bullets)
      bullet.Draw();
    player.Draw();
    enemy.Draw();
  EndMode2D();
  DrawText("Use WASD to move", 10, 10, 20, DARKGRAY);
  DrawText("Use OKL: to attack", 10, 30, 20, DARKGRAY);





  // Enemy
}

void Game::HandleInput()
{
  // Attack
  if(IsKeyDown(KEY_K))
    {
      playerAttackDirection.x += -1;
    }
  if(IsKeyDown(KEY_SEMICOLON))
    {
      playerAttackDirection.x += 1;
    }
  if(IsKeyDown(KEY_O))
    {
      playerAttackDirection.y += -1;
    }
  if(IsKeyDown(KEY_L))
    {
      playerAttackDirection.y += 1;
    }

  // Movement
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

  // Functions to move player and attack
  player.Move(deltaTime, playerDirection);
  player.Attack(playerAttackDirection);
  // Function to move background
  background.Move(deltaTime, playerDirection);
  // Resetting Directions
  playerDirection = {0, 0};
  playerAttackDirection = {0, 0};
}
