// Game.cpp
#include "Game.hpp"

/*
// Import Game Config
Game::Game()
{
    init(config);
}
 */

Game::Game() : m_window(), m_entities(), m_running(true) {}

void Game::init(void)
{
    // Create window
    m_window.create(sf::VideoMode({1280, 720}), "Test");
    m_window.setFramerateLimit(60);
    
    // Spawn Entities
}

void Game::run(void)
{
    while (m_running)
    {
        m_entities.update();
        Game::sRender();
        Game::sMovement();
        Game::sUserInput();
        Game::sCollision();
    }
    
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

// Set paused function

// Spawn Player function


