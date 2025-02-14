// Chunk.cpp
#include "Chunk.hpp"


Chunk::Chunk(Vec2 pos) : position(pos), cells(CHUNK_SIZE * CHUNK_SIZE, 0)
{
    generate();
}

void Chunk::generate()
{
    for (auto& cell : cells)
    {
        cell = rand() % 3;
    }
}
