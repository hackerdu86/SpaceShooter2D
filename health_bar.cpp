#pragma once
#include "include/raylib.h"
#define WINDOW_WIDTH 1400

class HealthBar
{
private:
    const int barLength = 20;
    int barWidth = 500;
    int x, y = 650;
    int hearthX = 0;
    char side = 'l';
    bool isHit = false;
    Texture2D hearthTextures[6] =
    {

    };
    void resetBar(char _side)
    {
        if (_side == 'r')
        {
            x = WINDOW_WIDTH - barWidth - 50;
            barWidth = 500;
        }
        barWidth = 500;
    }
public:
    //Constructors
    HealthBar(char _side)
    {
        if (_side == 'l')
            x = 0;
        if (_side == 'r')
        {
            x = WINDOW_WIDTH - barWidth;
            hearthX = WINDOW_WIDTH - 30;
            side = 'r';
        }
    }
    //Getters
    //Setters
    
    void setXPos(int _x)
    {
        x = _x;
    }
    void setHearthTextures(char *files[6])
    {
        for (int i = 0; i < 6; i++)
        {
            hearthTextures[i] = LoadTexture(files[i]);
        }
    }
    //Update Functions
    void update(bool _isHit, bool isEmpty)
    {
        if (_isHit)
        {
            if (side == 'l')
            {
                isHit = true;
                barWidth -= 50;
            }
            else
            {
                isHit = true;
                barWidth -= 50;
                x += 50;
            }
        }
        if (isEmpty)
            resetBar(side);
    }
    void draw()
    {
        DrawRectangle(x, y, barWidth, barLength, GREEN);
        if (isHit)
        {
            for (int i = 0; i < 6; i++)
            {
                DrawTexture(hearthTextures[i], hearthX, y, WHITE);
            }
            isHit = false;
        }
        else 
        {
            DrawTexture(hearthTextures[0], hearthX, y, WHITE);
        }
    }
};