// Components.hpp
#pragma once
#include "Common.hpp"

class CTransform
{
public:
    Vec2 pos = { 0.0, 0.0 };
    Vec2 velocity = { 0.0, 0.0 };
    float angle = 0;
    
    // Constructor
    CTransform(const Vec2 & p, const Vec2 & v, float a)
        : pos(p), velocity(v), angle(a) {}
};

class CShape
{
public:
    float radius;
    int points;
    SDL_Color fillColor;
    SDL_Color outlineColor;
    float thickness;
    
    /* Optimization tip
     SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
     Uint32 color = SDL_MapRGBA(format, fillColor.r, fillColor.g, fillColor.b, fillColor.a);

     // Now use `color` in the draw function:
     filledCircleColor(renderer, x, y, radius, color);
     */
    
    CShape(float r, int p, SDL_Color fill, SDL_Color outline, float thick)
            : radius(r), points(p), fillColor(fill), outlineColor(outline), thickness(thick) {}
    
    void draw(SDL_Renderer* renderer, int x, int y)
    {
        // Draw the filled circle
        filledCircleColor(renderer, x, y, radius, SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888),
                                fillColor.r, fillColor.g, fillColor.b, fillColor.a));
    }
    
    
    
    /*sf::CircleShape circle;
    
    CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline, float thickness)
        : circle(radius, points)
    {
        circle.setRadius(radius);
        circle.setPointCount(points);
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        //circle.setOrigin(radius);
    }
    
    // Circle Constructor
    
    // Paddle Constructor
     */
    
    
};

class CCollision
{
public:
    float radius = 0;
    CCollision(float r)
    : radius(r) {}
};

class CScore
{
public:
    int score = 0;
    
    CScore(int s)
    : score(s) {}
};

class CLifespan
{
public:
    int remaining = 0;
    int total = 0;
    
    CLifespan(int remain, int total)
        : remaining(remain), total(total) {}
};

class CInput
{
public:
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    
    bool shoot = false;
    
    CInput() {}
};
