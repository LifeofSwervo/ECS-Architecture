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

    spawnPlayer();
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
    // Ball movement
    for (const auto& entity : m_entities.getEntities("ball"))
    {
        if (entity->cShape)
        {
            if (m_ballPauseTimer > 0.0f)
            {
                m_ballPauseTimer -= GetFrameTime();
                return;
            }
            
            entity->cShape->center.x += entity->cTransform->velocity.x;
            entity->cShape->center.y += entity->cTransform->velocity.y;
        }
    }
    
    // Enemy Movement
}

void Game::sUserInput()
{
   for (const auto& entity : m_entities.getEntities("player"))
   {
       Vector2 movement = {0, 0};
       
       // Movement handling (y-axis)
       if (IsKeyDown(KEY_UP))
       {
           movement.y -= entity->cTransform->velocity.y;
       }
       if (IsKeyDown(KEY_DOWN))
       {
           movement.y += entity->cTransform->velocity.y;
       }
       
       entity->cShape->center.y += movement.y;
       
       if (entity->cShape->center.y < 0)
       {
           entity->cShape->center.y = 0;
       }
       if (entity->cShape->center.y + entity->cShape->rectSize.y > GetScreenHeight())
       {
           entity->cShape->center.y = GetScreenHeight() - entity->cShape->rectSize.y;
       }

       
   }
};

void Game::sRender(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Iterate over all entities and draw only those with a shape
    for (const auto& entity : m_entities.getEntities())
    {
        if (entity->cShape)
        {
            if (entity->tag() == "ball")
            {
                entity->cShape->DrawBall();
            }
            else if (entity->tag() == "player")
            {
                entity->cShape->DrawPaddle();
            }
            else if (entity->tag() == "enemy")
            {
                entity->cShape->DrawPaddle();
            }
        }
    }
    EndDrawing();
}

void Game::sCollision(void)
{
    // Ball collision
    for (const auto& entity : m_entities.getEntities("ball"))
    {
        
        
        if (CheckCollisionCircleRec(
                m_ball->cShape->center,
                m_ball->cShape->radius,
                {
                    m_player->cShape->center.x - m_player->cShape->rectSize.x / 2,
                    m_player->cShape->center.y - m_player->cShape->rectSize.y / 2,
                    m_player->cShape->rectSize.x,
                    m_player->cShape->rectSize.y
                }))
        {
            m_ball->cTransform->velocity.x *= -1;
        };
        
        if (CheckCollisionCircleRec(
                m_ball->cShape->center,
                m_ball->cShape->radius,
                {
                    m_enemy->cShape->center.x - m_player->cShape->rectSize.x / 2,
                    m_enemy->cShape->center.y - m_player->cShape->rectSize.y / 2,
                    m_enemy->cShape->rectSize.x,
                    m_enemy->cShape->rectSize.y
                }))
        {
            m_ball->cTransform->velocity.x *= -1;
        }
        
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
                entity->cShape->center.x = GetScreenWidth() / 2;
                entity->cShape->center.y = GetScreenHeight() / 2;
                m_ballPauseTimer = 2.0f;
            };
        }
    }
    
    // Player Collision
};


 void Game::spawnPlayer(void)
 {
     const float PLAYER_SPEED = 9;
     
     const Vector2 paddleSize = {20, 160};

     
     // Create Player
     auto entity = m_entities.addEntity("player");
     
     // cTransform is used to control the ball's velocity and angle.
     entity->cTransform = std::make_shared<CTransform>(Vector2{PLAYER_SPEED, PLAYER_SPEED}, 0.0f);
     
     // Entity Dimensions
     entity->cShape = std::make_shared<CShape>(Vector2{40, 720 / 2}, paddleSize, BLACK);
     
     // Set game's ball variable to be this entity
     m_player = entity;
 };
 
