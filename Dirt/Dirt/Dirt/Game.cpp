// Game.cpp
#include "Game.hpp"

//const int CELL_SIZE = 32;

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_running(true), m_windowSize{1280, 720} {
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
    m_window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowSize.width, m_windowSize.height, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // Spawn Entities
    
    // Start with initial chunk
    
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
    for (auto& entity : m_entities.getEntities())
    {
        if (entity->cTransform)
        {
            entity->cTransform->pos += entity->cTransform->velocity;
        }
    }
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
            } else if (entity->tag() == "player")
            {
                entity->cShape->draw(m_renderer, entity->cTransform->pos.x, entity->cTransform->pos.y);
            }
        }
    }
     
    
    SDL_RenderPresent(m_renderer);
}

void Game::sCollision(void)
{
    
    for (const auto& entity : m_entities.getEntities("ball"))
    {
        if (entity->cTransform->pos.y + entity->cShape->radius >= m_windowSize.height || entity->cTransform->pos.y - entity->cShape->radius <= 0)
        {
            entity->cTransform->velocity.y *= -1;
        }
    }
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
    
    // Grab value between 0 & 1.
    // If value is 1 return 1, if 0 return -1.
    int negRandomizerX = sGetRandomValue(0, 1) ? 1 : -1;
    int negRandomizerY = sGetRandomValue(0, 1) ? 1 : -1;
    
    // Properly initialize cShape before using it
        SDL_Color fillColor = {255, 255, 255, 255}; // Red color
        SDL_Color outlineColor = {0, 0, 0, 255}; // White outline
    
    
    auto entity = m_entities.addEntity("ball");
    
    // Spawn position and Velocity & angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowSize.width / 2, m_windowSize.height / 2), Vec2(BALL_SPEED * negRandomizerX, BALL_SPEED * negRandomizerY), 0.0f);
    
    // Radius, Points, Fill Color, Outline Color, Thickness
    entity->cShape = std::make_shared<CShape>();
    entity->cShape->setCircle(16.0f, 8, fillColor, outlineColor, 4.0f);

    
    
    // Input component so player can use inputs
    //entity->cInput = std::make_shared<CInput>();
    
    m_ball = entity;
}

void Game::spawnPlayer(void)
{
    const float PLAYER_SPEED = 0.0f;
    auto entity = m_entities.addEntity("player");
    
    SDL_Color fillColor = {255, 255, 255, 255};
    SDL_Color outlineColor = {0, 0, 0, 255};
    
    // Spawn position and Velocity & angle
    entity->cTransform = std::make_shared<CTransform>(Vec2(40, m_windowSize.height / 2), Vec2(PLAYER_SPEED, PLAYER_SPEED), 0.0f);
    
    
    entity->cShape = std::make_shared<CShape>();
    entity->cShape->setRectangle(20.0f, 100.0f, fillColor, outlineColor, 4.0f);

    
    m_player = entity;
}
