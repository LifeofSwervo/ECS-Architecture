#pragma once
//
//  Game.hpp
//  GW
//
//  Created by Paul Thomas on 11/22/24.
//


#include "Common.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

typedef enum GameScreen
{
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;



class Game
{
    EntityManager m_entities;

    std::shared_ptr<Entity> m_ball;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_enemy;

    int m_currentFrame = 0;
    float m_ballPauseTimer = 0.0f;
    int m_playerScore = 0;
    int m_enemyScore = 0;
    GameScreen m_currentScreen = TITLE; 



    // System functions
    void sMainMenu(void);
    void sMovement(void);       // System: Entity Position / Movement
    void sUserInput(void);
    void sLifespan(void);
    void sRender(void);         // System: Render / Drawing
    void sEnemySpawner(void);
    void sCollision(void);
    void sScoreHandler(void);
    void sBackground(void);
    void sEndScreen(void);
    void sReset(void);

    // Spawn Entites
    void spawnBall(void);
    void spawnPlayer(void);
    void spawnEnemy(void);
    
    


public:
    void init(void);
    void run(void);



};
