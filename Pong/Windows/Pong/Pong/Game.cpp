//  Game.cpp
#include "Game.hpp"

/*
// Import Game Config
Game::Game(const std::string & config)
{
    init(config);
}
*/

void Game::init(void)
{
    InitWindow(1280, 720, "GW");
    SetTargetFPS(60);

    //spawnBall();
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