#pragma once
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 700
#include "include/raylib.h"
#include <iostream>

using std::cout;
using std::endl;

class Laser
{
private:
    int lvelocity = 20;
    int rvelocity = -20;
    char side;
    int x, y;
    bool hasHitSomething = false;
    bool hasAlreadyHitSomething = false;
    Texture laserTexture;

public:
    //Constructors
    Laser(int _x, int _y, char _side) :  x(_x), y(_y), side(side)
    {
        
    }
    //Destructors

    //Getters
    int getXPos()
    {
        return x;
    }
    int getYPos()
    {
        return y;
    }
    bool getHasHitSomething()
    {
        return hasHitSomething;
    }
    bool getHasAlreadyHitSomething() 
    {
        return hasAlreadyHitSomething;
    }
    char getLaserSide()
    {
        return side;
    }
    //Setters
    void setXPos(int _x)
    {
        x = _x;
    }
    void setLaserTexture(char *filePath)
    {
        Image laserImage = LoadImage(filePath);
        ImageResize(&laserImage, 100, 50);
        laserTexture = LoadTextureFromImage(laserImage);
    }
    void setHasHitSomething(bool _hasHitSomething)
    {
        hasHitSomething = _hasHitSomething;
    }
    void setHasAlreadyHitSomething(bool _hasAlreadyHitSomething)
    {
        hasAlreadyHitSomething = _hasAlreadyHitSomething;
    }
    //Other Functions
    void tellSomething()
    {

    }
    //Update Function
    void update(char side)
    {
        if (side == 'l')
            x += lvelocity;
        if (side == 'r')
            x += rvelocity;    
    }
    //Draw Function
    void draw()
    {
        if (!hasHitSomething)
            DrawTexture(laserTexture, x+30, y, WHITE);
        
    }
};