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
