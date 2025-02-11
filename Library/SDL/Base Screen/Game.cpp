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
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // Spawn Entities
    spawnBall();
}

void Game::run(void)
{
    Uint32 frameStart;
    SDL_Event event;
    int frameTime;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    while (m_running)
    {
        frameStart = SDL_GetTicks();
        
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
        
        // Frame rate Control
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameTime < frameDelay) // If frame finished early
        {
            SDL_Delay(frameDelay - frameTime); // Delay to maintain fps
        }
        
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
        
    
    for (const auto& entity : m_entities.getEntities())
    {
        if (entity->cShape)
        {
            if (entity->tag() == "ball")
            {
                entity->cShape->draw(m_renderer, entity->cTransform->pos.x, entity->cTransform->pos.y);
            }
        }
    }
     
    
    SDL_RenderPresent(m_renderer);
}

void Game::sCollision(void)
{
    
}

int Game::sGetRandomValue(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
};


// Set paused function

void Game::spawnBall(void)
{
    const float BALL_SPEED = 5.0f;
    int screenHeight, screenWidth;
    SDL_GetWindowSize(m_window, &screenWidth, &screenHeight);
    int negRandomizer = sGetRandomValue(-1, 1);
    
    
    
    auto entity = m_entities.addEntity("ball");
    
    // Spawn position and Velocity & angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(screenWidth / 2, screenHeight / 2), Vec2(BALL_SPEED * negRandomizer, BALL_SPEED * negRandomizer), 0.0f);
    
    // Properly initialize cShape before using it
        SDL_Color fillColor = {255, 0, 0, 255}; // Red color
        SDL_Color outlineColor = {255, 255, 255, 255}; // White outline
    
    // Radius, Points, Fill Color, Outline Color, Thickness
    entity->cShape = std::make_shared<CShape>(32.0f, 8, fillColor, outlineColor, 4.0f);
    
    
    // Input component so player can use inputs
    //entity->cInput = std::make_shared<CInput>();
    
    m_ball = entity;
}
