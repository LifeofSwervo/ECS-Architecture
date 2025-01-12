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
    spawnPlayer();
    spawnEnemy();
}

void Game::run(void)
{
    switch (m_currentScreen)
    {
        case TITLE:
            sMainMenu();
            break;
        case GAMEPLAY:
            m_entities.update();
            sRender();
            sMovement();
            sUserInput();
            sCollision();

            // Check for win condition
            if (m_playerScore >= 10) {  // Example: Player wins at 10 points
                m_currentScreen = ENDING;
            } else if (m_enemyScore >= 10) {  // Example: Enemy wins at 10 points
                m_currentScreen = ENDING;
            }
            break;
        case ENDING:
            sEndScreen();
            break;
    }
}

//------------------------------------------------------------------------------------------
// System Functions
//------------------------------------------------------------------------------------------

void Game::sMainMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to the Game!", 400, 200, 40, BLACK);
    DrawText("Press ENTER to start", 450, 400, 20, BLACK);
    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) {
        m_currentScreen = GAMEPLAY;  // Switch to gameplay
    }
}


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
    for (const auto& entity : m_entities.getEntities("enemy"))
    {
        if (entity->cShape)
        {
            // Delta is the difference between the ball and enemy's y position
            float delta = m_ball->cShape->center.y - entity->cShape->center.y;

            // Ensures consistent movement
            float movement = std::clamp(delta, -entity->cTransform->velocity.y, entity->cTransform->velocity.y);
            
            entity->cShape->center.y += movement;
        }
    }
}

void Game::sUserInput()
{
    for (const auto& entity : m_entities.getEntities("player"))
    {
        Vector2 movement = { 0, 0 };

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
    }
};

void Game::sRender(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Game::sScoreHandler();
    Game::sBackground();

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
    const float MAX_BOUNCE_ANGLE = 75.0f * (PI / 180.0f);
    const float BALL_SPEED = 14.0f;
    
    // Ball collision
    for (const auto& entity : m_entities.getEntities("ball"))
    {
        // If Ball Collides with Player
        if (CheckCollisionCircleRec(
            m_ball->cShape->center,
            m_ball->cShape->radius,
            {
                m_player->cShape->center.x,
                m_player->cShape->center.y,
                m_player->cShape->rectSize.x,
                m_player->cShape->rectSize.y
            }))
        {
            //m_ball->cTransform->velocity.x *= -1;
            
            float relativeIntersectY = (m_player->cShape->center.y + (m_player->cShape->rectSize.y / 2)) - entity->cShape->center.y;
            float normalizedRelativeY = relativeIntersectY / (m_player->cShape->rectSize.y / 2);
            float bounceAngle = normalizedRelativeY * MAX_BOUNCE_ANGLE;
             
            entity->cTransform->velocity.x = BALL_SPEED * cos(bounceAngle);
            entity->cTransform->velocity.y = BALL_SPEED * -sin(bounceAngle);
            
        };

        // If ball collides with enemy
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
            //m_ball->cTransform->velocity.x *= -1;
            
            float relativeIntersectY = (m_enemy->cShape->center.y + (m_enemy->cShape->rectSize.y / 2)) - entity->cShape->center.y;
            float normalizedRelativeY = relativeIntersectY / (m_enemy->cShape->rectSize.y / 2);
            float bounceAngle = normalizedRelativeY * MAX_BOUNCE_ANGLE;
             
            entity->cTransform->velocity.x = BALL_SPEED * cos(bounceAngle);
            entity->cTransform->velocity.y = BALL_SPEED * -sin(bounceAngle);
            
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
            if (entity->cShape->center.x + entity->cShape->radius >= GetScreenWidth()) // Right Side of screen
              {
                // Reset ball functionality.
                entity->cTransform->velocity.x *= -1;
                entity->cShape->center.x = GetScreenWidth() / 2;
                entity->cShape->center.y = GetScreenHeight() / 2;
                m_ballPauseTimer = 2.0f;
                  
                  m_playerScore++;
              }
            else if (entity->cShape->center.x - entity->cShape->radius <= 0) // Left side of Screen
              {
                // Reset ball functionality.
                entity->cTransform->velocity.x *= -1;
                entity->cShape->center.x = GetScreenWidth() / 2;
                entity->cShape->center.y = GetScreenHeight() / 2;
                m_ballPauseTimer = 2.0f;
                  
                  m_enemyScore++;
              }
        }
    }

    // Player Collision
    for (const auto& entity : m_entities.getEntities("player"))
    {
        if (entity->cShape->center.y < 0)
        {
            entity->cShape->center.y = 0;
        }
        if (entity->cShape->center.y + entity->cShape->rectSize.y > GetScreenHeight())
        {
            entity->cShape->center.y = GetScreenHeight() - entity->cShape->rectSize.y;
        }
    }

    // Enemy Collision
    for (const auto& entity : m_entities.getEntities("enemy"))
    {
        // Enemy Screen Constraints
        if (entity->cShape->center.y < 0)
        {
            entity->cShape->center.y = 0;
        };
        if (entity->cShape->center.y + entity->cShape->rectSize.y > GetScreenHeight())
        {
            entity->cShape->center.y = GetScreenHeight() - entity->cShape->rectSize.y;
        };
    };
};

void Game::sScoreHandler(void)
{
    DrawText(TextFormat("Player: %d", m_playerScore), 20, 20, 20, BLACK);
    DrawText(TextFormat("Enemy: %d", m_enemyScore), GetScreenWidth() - 140, 20, 20, BLACK);
}

void Game::sBackground(void)
{
    Vector2 bisectorTop = {static_cast<float>(GetScreenWidth()) / 2, 0.0f};
    Vector2 bisectorBottom = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight())};
    DrawLineV(bisectorTop, bisectorBottom, BLACK);
}

void Game::sEndScreen() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Game Over!", 500, 300, 40, BLACK);
    DrawText(TextFormat("Player Score: %d", m_playerScore), 500, 350, 20, BLACK);
    DrawText(TextFormat("Enemy Score: %d", m_enemyScore), 500, 380, 20, BLACK);
    DrawText("Press R to Restart or ESC to Quit", 450, 500, 20, BLACK);
    EndDrawing();

    if (IsKeyPressed(KEY_R)) {
        sReset();  // Function to reset variables and entities
        m_currentScreen = TITLE;  // Go back to the main menu
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();  // Quit game
    }
}

void Game::sReset() {
    m_playerScore = 0;
    m_enemyScore = 0;
    spawnBall();
    spawnPlayer();
    spawnEnemy();
}


void Game::spawnBall(void)
{
    const float BALL_SPEED = 14;

    // Create ball
    auto entity = m_entities.addEntity("ball");

    // cTransform is used to control the ball's velocity and angle.
    entity->cTransform = std::make_shared<CTransform>(Vector2{ BALL_SPEED, BALL_SPEED }, 0.0f);

    // Entity Dimensions
    entity->cShape = std::make_shared<CShape>(Vector2{ 1280 / 2,720 / 2 }, 20.0f, BLACK);

    // Set game's ball variable to be this entity
    m_ball = entity;
};


void Game::spawnPlayer(void)
{
    const float PLAYER_SPEED = 12;

    const Vector2 paddleSize = { 20, 160 };


    // Create Player
    auto entity = m_entities.addEntity("player");

    // Velocity & Angle
    entity->cTransform = std::make_shared<CTransform>(Vector2{ PLAYER_SPEED, PLAYER_SPEED }, 0.0f);

    // Coordinates, size, & color
    entity->cShape = std::make_shared<CShape>(Vector2{ 40, 720 / 2 }, paddleSize, BLACK);

    m_player = entity;
};

void Game::spawnEnemy(void)
{
    const float ENEMY_SPEED = 11;
    const Vector2 PADDLE_SIZE = { 20, 160 };

    // Create Enemy
    auto entity = m_entities.addEntity("enemy");

    // Velocity & Angle
    entity->cTransform = std::make_shared<CTransform>(Vector2{ ENEMY_SPEED, ENEMY_SPEED }, 0.0f);

    // Coordinates, size, & color
    entity->cShape = std::make_shared<CShape>
        (
        Vector2{ static_cast<float>(GetScreenWidth() - 40 - PADDLE_SIZE.x), 720 / 2 },
        PADDLE_SIZE,
        BLACK
        );

    m_enemy = entity;

}
