// ChunkManager.hpp
#pragma once
#include <unordered_map>
#include "Chunk.hpp"

class ChunkManager
{
// Private
    std::unordered_map<std::string, std::shared_ptr<Chunk>> chunks;

    std::string getChunkKey(Vec2 pos);
public:
    std::shared_ptr<Chunk> getChunk(Vec2 pos);
    void updateChunks(Vec2 playerPos);
};
