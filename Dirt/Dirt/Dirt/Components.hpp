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

enum class ShapeType
{
    Circle,
    Rectangle
};

class CShape
{
public:
    ShapeType type;
    SDL_Color fillColor, outlineColor;
    float outlineThickness;
    
    // Circle Properties
    float radius;
    int points;

    // Rectangle Properties
    float width, height;
    
    /* Optimization tip
     SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
     Uint32 color = SDL_MapRGBA(format, fillColor.r, fillColor.g, fillColor.b, fillColor.a);

     // Now use `color` in the draw function:
     filledCircleColor(renderer, x, y, radius, color);
     */
    
    CShape() : type(ShapeType::Circle), radius(0), points(0), width(0), height(0), outlineThickness(0) {}

    void setCircle(float r, int p, SDL_Color fill, SDL_Color outline, float thickness)
    {
        type = ShapeType::Circle;
        radius = r;
        points = p;
        fillColor = fill;
        outlineColor = outline;
        outlineThickness = thickness;
    }

    
    void setRectangle(float w, float h, SDL_Color fill, SDL_Color outline, float thickness) {
        type = ShapeType::Rectangle;
        width = w;
        height = h;
        fillColor = fill;
        outlineColor = outline;
        outlineThickness = thickness;
    }
    
    void draw(SDL_Renderer* renderer, float x, float y)
    {
        if (type == ShapeType::Circle)
        {
            filledCircleColor(renderer, x, y, radius, SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888),
                                            fillColor.r, fillColor.g, fillColor.b, fillColor.a));
        } else if (type == ShapeType::Rectangle)
        {
            SDL_Rect rect = { static_cast<int>(x - width / 2), static_cast<int>(y - height / 2), static_cast<int>(width), static_cast<int>(height) };
            SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
            SDL_RenderFillRect(renderer, &rect);
        }
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
