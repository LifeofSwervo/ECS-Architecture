// Game.hpp
#pragma once
#include "Common.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    //sf::Font m_font;
    //sf::Text m_text;

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
    void init(void);
    void run(void);
};
