// Chunk.hpp
#pragma once
#include "Common.hpp"

constexpr int CHUNK_SIZE = 16;

class Chunk
{
public:
    Vec2 position;

    // Stores terrain type
    // (0 = grass, 1 = dirt, etc)
    std::vector<int> cells;
    std::vector<std::pair<int, int>> treePositions;

    Chunk(Vec2 pos);
    void generate();
    void render(SDL_Renderer* renderer, Vec2 cameraPos);
};