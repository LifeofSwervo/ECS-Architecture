//  Game.cpp
#include "Game.hpp"

void Game::init(void)
{
    InitWindow(1280, 720, "GW");
    SetTargetFPS(60);
}

void Game::run(void)
{
    Game::sRender();
}

void Game::sRender(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
}

void Game::spawnBall(void)
{
    // Create ball

    // Give cTransform so it spawns in middle of screen

    // Entity Dimensions

    // Set game's ball variable to be this entity

}