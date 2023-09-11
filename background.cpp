#pragma once
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 700
#include "include/raylib.h"

class Background
{

private:
    int firstX = 0, secondX = 1400, y = 0;
    int velocity = 1;
    Texture2D firstTexture;
    Texture2D secondTexture;
public:
    Background()
    {

    }
    void setTwoBackgroundTextures(char *filePath)
    {
        Image first = LoadImage(filePath);
        ImageResize(&first, WINDOW_WIDTH, WINDOW_HEIGHT);
        firstTexture = LoadTextureFromImage(first);
        secondTexture = LoadTextureFromImage(first);
    }
    void update()
    {
        if (firstX <= -1400)
            firstX = 1400;
        if (secondX <= - 1400)
            secondX = 1400;
        
        firstX -= velocity;
        secondX -= velocity;
    }
    void draw()
    {
        DrawTexture(firstTexture, firstX, y, WHITE);
        DrawTexture(secondTexture, secondX, y, WHITE);
        DrawCircle3D({3.0f, 9.0f, 3.0f, }, 30.0f, {3.0f, 9.0f, 3}, 9.0f, MAGENTA);
    }
};