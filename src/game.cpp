#include "../include/game.h"

Game::Game()
{
  playerDirection = {0, 0};
  playerAttackDirection = {0, 0};
  deltaTime = 0.0f;
  spawnRadius = 250.0f;
  SpawnEnemies(1, 15);
  //SpawnEnemies(2, 5);
  //SpawnEnemies(3, 5);
  //SpawnEnemies(4, 5);
  //SpawnEnemies(5, 5);

}

Game::~Game()
{
  background.UnloadImages();
  PlayerBullet::UnloadImage();
  Enemy::UnloadImages();
  EnemyBullet::UnloadImage();
}

void Game::Update()
{
  // Updating deltaTime
  deltaTime = GetFrameTime();

  // Player Input
  HandleInput();

  // delete inactive player bullets
  for (auto it = playerBullets.begin(); it != playerBullets.end();)
    {
      // If the bullet's timeActive is >= 1.5 seconds, remove it
      if (it->ShouldDelete())
        {
          it = playerBullets.erase(it); // Erase the bullet and move to the next
        }
      else
        {
          ++it; // Otherwise, just move to the next bullet
        }
    }

  // Move active player bullets
  for(auto& bullet: playerBullets)
    bullet.Move(deltaTime);

  // Background
  background.Update();

  // Savepoint

  // Enemy
  for(auto& enemy: enemies)
    {
      enemy.Move(deltaTime, player.position);
      enemy.Attack(enemyBullets);
    }

  // Delete old enemy bullets
  for(auto it = enemyBullets.begin(); it != enemyBullets.end();)
    {
      if(it->ShouldDelete())
        it = enemyBullets.erase(it);
      else
        ++it;
    }

  // Move active enemy bullets
  for(auto& bullet: enemyBullets)
    {
      bullet.Move(deltaTime);
    }


}

void Game::Draw()
{
  // Background
  background.Draw();

  // Savepoint
  // ...

  BeginMode2D(player.camera);

    // Drawing player bullets
    for(auto& bullet: playerBullets)
      bullet.Draw();

    //Drawing enemy bullets

    for(auto& bullet: enemyBullets)
      {
        bullet.Draw();
      }

    // Drawing player
    player.Draw();

    // Enemy
    for(auto& enemy: enemies)
      enemy.Draw();

  EndMode2D();

  DrawText("Use WASD to move", 10, 10, 20, DARKGRAY);
  DrawText("Use Arrows to attack", 10, 30, 20, DARKGRAY);
  DrawText(TextFormat("Player's health is %d", player.GetHealth()), 10, 50, 20, DARKGRAY);
}

void Game::HandleInput()
{
  // Attack
  if(IsKeyDown(KEY_LEFT))
    playerAttackDirection.x += -1;
  if(IsKeyDown(KEY_RIGHT))
    playerAttackDirection.x += 1;
  if(IsKeyDown(KEY_UP))
    playerAttackDirection.y += -1;
  if(IsKeyDown(KEY_DOWN))
    playerAttackDirection.y += 1;

  // Movement
  if(IsKeyDown(KEY_A))
    playerDirection.x += -1;
  if(IsKeyDown(KEY_D))
    playerDirection.x += 1;
  if(IsKeyDown(KEY_W))
    playerDirection.y += -1;
  if(IsKeyDown(KEY_S))
    playerDirection.y += 1;

  // Functions to move player and attack
  player.Move(deltaTime, playerDirection);
  player.Attack(playerAttackDirection, playerBullets);
  // Function to move background
  background.Move(deltaTime, playerDirection);
  // Resetting Directions
  playerDirection = {0, 0};
  playerAttackDirection = {0, 0};
}

void Game::SpawnEnemies(int type, int number)
{
  //TraceLog(LOG_INFO, "spawnRadius = %.2f", spawnRadius);

  for (int i = 0; i < number; i++)
    {
      // Generate a random angle in radians
      float angle = GetRandomValue(0, 359) * DEG2RAD;

      // Calculate x and y coordinates on the circle
      float x = player.position.x + spawnRadius * cos(angle);
      float y = player.position.y + spawnRadius * sin(angle);

      // Add the new enemy to the list
      enemies.push_back(Enemy({x, y}, type));
    }
}

void Game::CheckForCollisions()
{
  // PlayerBullet collision
  for(auto& bullet: playerBullets)
    {
      // with Enemies
      auto it = enemies.begin();
      while(it != enemies.end())
        {
          if(CheckCollisionCircles(bullet.GetCollisionPosition(), bullet.GetCollisionRadius(), it->GetCollisionPosition(), it->GetCollisionRadius()))
            {
              it = enemies.erase(it);
              bullet.shouldBeDestroyed = true;
            }
          else
            {
              ++it;
            }
        }

      // with EnemyBullets
      for(auto& enemyBullet: enemyBullets)
        {
          if(CheckCollisionCircles(bullet.GetCollisionPosition(), bullet.GetCollisionRadius(), enemyBullet.GetCollisionPosition(), enemyBullet.GetCollisionRadius()))
            {
              enemyBullet.shouldBeDestroyed = true;
              bullet.Penetrate();
            }
        }
    }

  for(auto& bullet: enemyBullets)
    {
      if(CheckCollisionCircles(bullet.GetCollisionPosition(), bullet.GetCollisionRadius(), player.GetCollisionPosition(), player.GetCollisionRadius()))
        {
          bullet.shouldBeDestroyed = true;
          player.DealDamage(1);
        }
    }
}
