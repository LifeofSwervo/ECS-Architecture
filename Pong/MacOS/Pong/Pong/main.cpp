/*******************************************************************************************
 * Main Screen Manager.
 * Author: Clarence Thomas
 * Description - Provides a blank template of code containing different game states.
 *************************************************************************************************************************************************/
#include "Game.hpp"

int main(void)
{
    Game g;
    g.init();
    while (!WindowShouldClose())
    {
        g.run();

    }
    // TODO: Unload all loaded data (textures, fonts, audio) here!
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
