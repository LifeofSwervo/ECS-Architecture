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
class Game
{
    EntityManager m_entities;
    int m_currentFrame = 0;



    // System functions
    void sRender(void);


    void spawnBall();

public:
    void init(void);
    void run(void);



};
