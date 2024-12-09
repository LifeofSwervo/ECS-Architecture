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
            std::cout << "working";
            
        }
    }

    
    EndDrawing();
}

void Game::spawnBall(void)
{
    // Create ball
    auto entity = m_entities.addEntity("ball");

    // Give cTransform so it spawns in middle of screen
    //entity->cTransform = std::make_shared<CTransform>(Vec2(1280 / 2, 720 / 2), Vec2(0, 0), 0.0f);

    // Entity Dimensions
    entity->cShape = std::make_shared<CShape>(Vector2{1280 / 2, 720 / 2}, 32.0f, BLACK, BLACK, 4.0f);

    
    // Set game's ball variable to be this entity
    m_ball = entity;
    
    
}
