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
    static FastNoiseLite terrainNoise, treeNoise;
    terrainNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    terrainNoise.SetFrequency(0.063f);

    treeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    treeNoise.SetFrequency(0.2f); // Higher frequency for more variation

    for (int y = 0; y < CHUNK_SIZE; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            float worldX = (position.x * CHUNK_SIZE + x);
            float worldY = (position.y * CHUNK_SIZE + y);

            // Get terrain noise value
            float terrainNoiseValue = (terrainNoise.GetNoise(worldX, worldY) + 1.0f) / 2.0f;

            // Determine terrain type
            int terrainType = (terrainNoiseValue < 0.99f) ? 0 : 2; // Grass or Stone
            cells[y * CHUNK_SIZE + x] = terrainType;

            // If grass, determine if a tree should spawn
            if (terrainType == 0) // Only place trees on grass
            {
                float treeNoiseValue = (treeNoise.GetNoise(worldX, worldY) + 1.0f) / 2.0f;
                if (treeNoiseValue > 0.85f) // Adjust threshold for density
                {
                    treePositions.push_back({x, y}); // Store tree locations
                }
            }
        }
    }
}


void Chunk::render(SDL_Renderer *renderer, Vec2 cameraPos)
{
    //const int CELL_SIZE = 64;

    // Convert chunk position to world coordinates (pixels)
    int chunkWorldX = position.x * CHUNK_SIZE * CELL_SIZE;
    int chunkWorldY = position.y * CHUNK_SIZE * CELL_SIZE;

    for (int y = 0; y < CHUNK_SIZE; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            int cellType = cells[y * CHUNK_SIZE + x];

            // Convert cell position relative to the chunk
            int worldX = chunkWorldX + x * CELL_SIZE;
            int worldY = chunkWorldY + y * CELL_SIZE;


            // Convert world coordinates to screen space relative to the camera
            int renderX = worldX - (int)cameraPos.x + (1280 / 2);
            int renderY = worldY - (int)cameraPos.y + (720 / 2);


            SDL_Rect cellRect = { renderX, renderY, CELL_SIZE, CELL_SIZE };

            // Set colors for Cell Terrain Type
            if (cellType == 0) SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Grass
            else if (cellType == 1) SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Dirt
            else SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Stone

            SDL_RenderFillRect(renderer, &cellRect);

            // Outline in white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    for (const auto& tree : treePositions)
    {
        int worldX = chunkWorldX + tree.first * CELL_SIZE;
        int worldY = chunkWorldY + tree.second * CELL_SIZE;
        int renderX = worldX - cameraPos.x + (1280 / 2);
        int renderY = worldY - cameraPos.y + (720 / 2);
        
        SDL_Rect treeRect = { renderX, renderY, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(renderer, &treeRect);
    }
}

