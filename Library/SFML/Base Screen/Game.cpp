// Game.cpp
#include "Game.hpp"

/*
// Import Game Config
Game::Game()
{
    init(config);
}
 */

//Game::Game() : m_window(), m_entities(), m_running(true) {}

Game::Game(void)
{
    init();
}

void Game::init(void)
{
    // Create window
    m_window.create(sf::VideoMode({1280, 720}), "Test");
    m_window.setFramerateLimit(60);
    
    // Spawn Entities
    spawnPlayer();
}

void Game::run(void)
{
    while (m_window.isOpen()) // Main game loop
    {
        // Handle window events
        while (const std::optional event = m_window.pollEvent())
        {
            // Handle window close event
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
            // Handle key press event (example: Escape key)
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    m_window.close();
                }
            }
        }

        // Game logic
        m_entities.update();  // Update entities
        sMovement();          // Handle movement
        sUserInput();         // Handle user input
        sCollision();         // Handle collisions

        // Rendering
        //m_window.clear();   Delete 
        sRender();            // Render objects to the screen
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
    m_window.clear();
    
    for (const auto& entity : m_entities.getEntities())
    {
        if (entity->cShape)
        {
            if (entity->tag() == "player")
            {
                m_window.draw(entity->cShape->circle);
            }
        }
    }
    
    m_window.display();
}

void Game::sCollision(void)
{
    
}

// Set paused function

// Spawn Player function
void Game::spawnPlayer(void)
{
    auto entity = m_entities.addEntity("player");
    
    // Spawn position and Velocity & angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
    
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    
    entity->cShape->circle.setPosition({entity->cTransform->pos.x, entity->cTransform->pos.y});
    
    // Input component so player can use inputs
    entity->cInput = std::make_shared<CInput>();
    
    m_player = entity;
}


