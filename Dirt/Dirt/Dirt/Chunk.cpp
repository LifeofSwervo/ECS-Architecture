// Chunk.cpp
#include "Chunk.hpp"

/**
 * @brief Constructor for the Chunk class.
 *
 * @param pos Position of the chunk.
 *
 * @note Initilizes the chunk's grid then calls Generate function.
 */
Chunk::Chunk(Vec2 pos) : position(pos), cells(CHUNK_SIZE * CHUNK_SIZE, 0)
{
    generate();
}

/**
 * @brief Populates each cell in the chunk with a random value between 0 & 2 (inclusive).
 */
void Chunk::generate()
{
    // Placeholder Algorithm
    for (auto& cell : cells)
    {
        cell = rand() % 3;
    }
}

void Chunk::render(SDL_Renderer *renderer)
{
    const int CELL_SIZE = 16;
    
    for (int y = 0; y < CHUNK_SIZE; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            int cellType = cells[y * CHUNK_SIZE + x];
            
            SDL_Rect cellRect = {
                (int)(position.x * CHUNK_SIZE * CELL_SIZE + x * CELL_SIZE),
                (int)(position.y * CHUNK_SIZE * CELL_SIZE + y * CELL_SIZE),
                CELL_SIZE, CELL_SIZE
            };
            
            // Set colors for Cell Terrain Type
            if (cellType == 0) SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Grass
            else if (cellType == 1) SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Dirt
            else SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Stone
            
            SDL_RenderFillRect(renderer, &cellRect);
            
            // Outline in black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }
}
