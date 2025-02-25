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
    // Set 2D perlin noise scale to 0.1
    static FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.1f);
    
    // Loop through chunk size
    for (int y = 0; y < CHUNK_SIZE; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            float worldX = (position.x * CHUNK_SIZE + x);
            float worldY = (position.y * CHUNK_SIZE + y);
            
            // Remap noise value from [-1, 1] to [0, 1]
            float noiseValue = (noise.GetNoise(worldX, worldY) + 1.0f) / 2.0f;
            
            // Map the noies value to the terrain type
            int terrainType;
            /*
            if (noiseValue > 0.6f) //noiseValue > 0.6f
            {
                terrainType = 0; // Grass
            } else if (noiseValue > 0.3f) //noiseValue > 0.3f
            {
                terrainType = 1; // Dirt
            } else
            {
                terrainType = 2; // Stone
            }
             */
            if (noiseValue < 0.9f)
            {
                terrainType = 0; // Grass
            } else
            {
                terrainType = 2; // Stone
            }
            
            // Store terrainType in cells
            cells[y * CHUNK_SIZE + x] = terrainType;
        }
    }
}

void Chunk::render(SDL_Renderer *renderer, Vec2 cameraPos)
{
    const int CELL_SIZE = 16;

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
}

