#pragma once
#include "font.cpp"
#include "include/raylib.h"

Font::Font(string &_text, int _x, int _y) : text(_text), x(_x), y(_x)
{
   textLength = text.length();
}
void Font::setTextTextures()
{
    for (int i = 0; i < textLength; i++)
    {
        filePath[textLength - 1] = text.at(i);
        textTextures.at(0) = LoadTexture(filePath);
    }
}
void Font::draw()
{
    for (int i = 0; i < textLength; i++)
    {
        DrawTexture(textTextures.at(i), x+(i*distanceBetweenLetters), y, WHITE);
    }
}