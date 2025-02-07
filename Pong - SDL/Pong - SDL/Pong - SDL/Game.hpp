// Game.hpp
#pragma once
#include "Common.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

class Game
{
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    EntityManager m_entities;

    std::shared_ptr<Entity> m_ball;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_enemy;

    int m_currentFrame = 0;
    bool m_running = true;
    
    void init(const std::string & config);



    // System functions
    void sMovement(void);       // System: Entity Position / Movement
    void sUserInput(void);
    void sLifespan(void);
    void sRender(void);         // System: Render / Drawing
    void sEnemySpawner(void);
    void sCollision(void);

    // Spawn Entites
    void spawnBall(void);
    void spawnPlayer(void);
    void spawnEnemy(void);

public:
    Game();
    ~Game();
    void init(void);
    void run(void);
};
