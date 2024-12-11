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

    spawnBall();
}

void Game::run(void)
{
    m_entities.update();
    Game::sRender();
    Game::sMovement();
    Game::sCollision();
}

//------------------------------------------------------------------------------------------
// System Functions
//------------------------------------------------------------------------------------------

void Game::sMovement(void)
{
    // Ball movement
    for (const auto& entity : m_entities.getEntities())
    {
        if (entity->cShape)
        {
            entity->cShape->center.x += entity->cTransform->velocity.x;
            entity->cShape->center.y += entity->cTransform->velocity.y;
        }
    }
}

void Game::sRender(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Iterate over all entities and draw only those with a shape
    for (const auto& entity : m_entities.getEntities())
    {
        if (entity->cShape)
        {
            entity->cShape->Draw();
        }
    }
    EndDrawing();
}

void Game::sCollision(void)
{
    // Ball collision
    for (const auto& entity : m_entities.getEntities("ball"))
    {
        // Check for ball touching screen constraints
        if (entity->cShape && entity->cTransform)
        {
            // Checks Y axis of screen.
            if (entity->cShape->center.y + entity->cShape->radius >= GetScreenHeight() || entity->cShape->center.y - entity->cShape->radius <= 0)
            {
                entity->cTransform->velocity.y *= -1;
            }
            
            // Check X axis of screen.
            if (entity->cShape->center.x + entity->cShape->radius >= GetScreenWidth() || entity->cShape->center.x - entity->cShape->radius <= 0)
            {
                // Reset ball functionality.
                entity->cTransform->velocity.x *= -1;
                float midScreenX = GetScreenWidth() / 2;
                float midScreenY = GetScreenHeight() / 2;
                
                entity->cShape->center.x = midScreenX;
                entity->cShape->center.y = midScreenY;
            };
        }
    }
    
    // Player Collision
};

void Game::spawnBall(void)
{
    const float BALL_SPEED = 5;
    // Create ball
    auto entity = m_entities.addEntity("ball");

    // cTransform is used to control the ball's velocity and angle. 
    entity->cTransform = std::make_shared<CTransform>(Vector2{BALL_SPEED, BALL_SPEED}, 0.0f);

    // Entity Dimensions
    entity->cShape = std::make_shared<CShape>(Vector2{1280 / 2,720 / 2}, 32.0f, BLACK, BLACK, 4.0f);
    

    
    // Set game's ball variable to be this entity
    m_ball = entity;
    
    
}
