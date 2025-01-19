// Game.cpp
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
    // Create window
    // Set FPS (60)
    
    // Spawn Entities
}

void Game::run(void)
{
    m_entities.update();
    Game::sRender();
    Game::sMovement();
    Game::sUserInput();
    Game::sCollision();
}

//------------------------------------------------------------------------------------------
// System Functions
//------------------------------------------------------------------------------------------

void Game::sMovement(void)
{
    
}

void Game::sUserInput(void)
{
    
}

void Game::sRender(void)
{
    
}

void Game::sCollision(void)
{
    
}



