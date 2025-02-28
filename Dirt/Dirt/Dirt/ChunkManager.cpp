// ChunkManager.cpp
#include "ChunkManager.hpp"

// Create Unique Key based off chunk pos
std::string ChunkManager::getChunkKey(Vec2 pos)
{
    return std::to_string((int)pos.x) + "," + std::to_string((int)pos.y);
}

std::shared_ptr<Chunk> ChunkManager::getChunk(Vec2 pos)
{
    // Create unique string (key) for Chunk pos
    std::string key = getChunkKey(pos);
    
    auto [it, inserted] = chunks.emplace(key, nullptr);
    if (inserted)
    {
        it->second = std::make_shared<Chunk>(pos);
    }
    
    return it->second;
    
    /*
    // Check if key exist in chunks map
    if (chunks.find(key) == chunks.end())
    {
        std::cout << "Generating new chunk at: " << key << std::endl;
        // If it exist grab that key
        chunks[key] = std::make_shared<Chunk>(pos);
    }
    */
    
    // If not create a new one
    return chunks[key];
}

/**
 * @brief Updates / Loads a chunk in  an area around the player's position.
 *
 * @param playerPos  Position of the player.
 */
void ChunkManager::updateChunks(Vec2 playerPos)
{
    // Used to find what chunk player is in
    int chunkX = (int)playerPos.x / (CHUNK_SIZE * 16);
    int chunkY = (int)playerPos.y / (CHUNK_SIZE * 16);
    

    
    // Interate over a 3x3 region of chunks, centered on the chunk with the player
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            // Ensure if a chunk is not created, it's created
            auto chunk = getChunk(Vec2(chunkX + dx, chunkY + dy));
        }
    }
}

std::unordered_map<std::string, std::shared_ptr<Chunk>>& ChunkManager::getLoadedChunks()
{
    return chunks;
}

