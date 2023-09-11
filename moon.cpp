#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "include/raylib.h"

using std::string;
using std::vector;
using std::to_string;
using std::cout;
using std::endl;

class Moon
{
private:
    float x = 750.0f, y = 200.0f;
    int counter = 0;
    int imgTurn = 0;
    Texture2D moonFramesList[59]
    {

    };
public:
    Moon()
    {

    }
    void setMoonFrames(string filesPath)
    {   
        string temp = filesPath;
        for (int i = 1; i < 60; i++)
        {
            filesPath = temp;
            filesPath += to_string(i);
            filesPath += ".png";
            char *realFilesPath = new char[filesPath.length() + 5];
            strcpy(realFilesPath, filesPath.c_str());
            Image moonFrame = LoadImage(realFilesPath);
            ImageResize(&moonFrame, 100, 100);
            moonFramesList[i] = LoadTextureFromImage(moonFrame);
            delete [] realFilesPath;
        }
    }
    void update()
    {
        counter++;
        if (counter % 6 != 0)
        {
            return;
        }
        if (imgTurn == 59)
        {
            imgTurn = 0;
            return;
        }
        imgTurn++;
        x -= 0.2f;
    }
    void draw()
    {
        DrawTexture(moonFramesList[imgTurn], x, y, WHITE);
    }
};