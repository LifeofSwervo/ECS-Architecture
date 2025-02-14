// Chunk.hpp
#pragma once
#include "Common.hpp"

const int CHUNK_SIZE = 16;

class Chunk
{
public:
    Vec2 position;
    
    // Stores terrain type
    // (0 = grass, 1 = dirt, etc)
    std::vector<int> cells;
    
    Chunk(Vec2 pos);
    void generate();
};
