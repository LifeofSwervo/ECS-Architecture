#pragma once
//
//  Game.hpp
//  GW
//
//  Created by Paul Thomas on 11/22/24.
//


#include "Common.hpp"
#include <stdio.h>

class Game
{
    int m_currentFrame = 0;



    // System functions
    void sRender(void);


    void spawnBall();

public:
    void init(void);
    void run(void);



};

