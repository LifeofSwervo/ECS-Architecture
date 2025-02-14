// ChunkManager.cpp
#include "ChunkManager.hpp"

std::string ChunkManager::getChunkKey(Vec2 pos)
{
    return std::to_string((int)pos.x) + "," + std::to_string((int)pos.y);
}

std::shared_ptr<Chunk> ChunkManager::getChunk(Vec2 pos)
{
    std::string key = getChunkKey(pos);
    if (chunks.find(key) == chunks.end())
    {
        chunks[key] = std::make_shared<Chunk>(pos);
    }
    return chunks[key];
}

void ChunkManager::updateChunks(Vec2 playerPos)
{
    int chunkX = (int)playerPos.x / CHUNK_SIZE;
    int chunkY = (int)playerPos.y / CHUNK_SIZE;
    
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            getChunk(Vec2(chunkX + dx, chunkY + dy)); // Load neighboring chunks
        }
    }
}
