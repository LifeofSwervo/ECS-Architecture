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

Game::~Game()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::init(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create window
    m_window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    
    // Spawn Entities
    spawnPlayer();
}

void Game::run(void)
{
    SDL_Event event;
    
    while (m_running)
    {
        // Handle window events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_running = false;
            }
        }
        // Game Logic
        m_entities.update();  // Update entities
        sMovement();          // Handle movement
        sUserInput();         // Handle user input
        sCollision();         // Handle collisions

        // Rendering
        sRender();
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
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
        
    /*
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
     */
    
    SDL_RenderPresent(m_renderer);
}

void Game::sCollision(void)
{
    
}

// Set paused function

// Spawn Player function
void Game::spawnPlayer(void)
{
    /*
    auto entity = m_entities.addEntity("player");
    
    // Spawn position and Velocity & angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
    
    // Radius, Points, Fill Color, Outline Color, Thickness
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    
    entity->cShape->circle.setPosition({entity->cTransform->pos.x, entity->cTransform->pos.y});
    
    // Input component so player can use inputs
    entity->cInput = std::make_shared<CInput>();
    
    m_player = entity;
     */
}
