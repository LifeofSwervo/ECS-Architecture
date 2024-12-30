#pragma once
// Components.hpp
#include "Common.hpp"


class CTransform
{
public:
    Vector2 velocity;
    float angle = 0;

    // Constructor
    CTransform(const Vector2& v, float a)
        : velocity(v), angle(a) {}
};


class CShape
{
public:
    Vector2 center;
    Vector2 rectSize;
    float radius;
    Color fillColor;
    Color outlineColor;
    float outlineThickness;

    /*
    // Default constructor
    CShape(Vector2 center, float radius, Color fill, Color outline, float thickness)
        : center(center), radius(radius), fillColor(fill), outlineColor(outline), outlineThickness(thickness) {}
     */

     /*// Default Constructor
     CShape(Vector2 center, Color fillColor)
         : center(center), fillColor(fillColor) {}
      */

      // Circle Constructor
    CShape(Vector2 center, float radius, Color fillColor)
        : center(center), radius(radius), fillColor(fillColor) {}

    // Paddle Constructor
    CShape(Vector2 center, Vector2 rectSize, Color fillColor)
        : center(center), rectSize(rectSize), fillColor(fillColor) {}

    void DrawBall() const
    {
        DrawCircleV(center, radius, fillColor);
        /*if (outlineThickness > 0)
        {
            DrawCircleLines(center.x, center.y, radius + outlineThickness, outlineColor);
        }
        */
    }

    void DrawPaddle() const
    {
        DrawRectangleV(center, rectSize, fillColor);
    }
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
    int remaining = 0; // "Amount of total lifespan remaining on the enemy"
    int total = 0; // "The total initial amount of lifespan"

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