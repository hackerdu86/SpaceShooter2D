#include "include/raylib.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Text
{
private:
    const int distanceBetweenLetters = 30;
    int textLength;
    int asciiA = 65;
    int filePathLength = 33;
    int x, y;
    string text;
    Texture2D alphabetTextures[26] =
    {

    };
public:
    //Constructors
    Text(string _text, int _x, int _y) : text(_text), x(_x), y(_x)
    {
        textLength = text.length();
    }
    //Getters
    //Setters
    void setAlphabetTextures(char *filePath)
    {
        for (int i = 0; i < 26; i++)
        {
            filePath[filePathLength - 4] = asciiA + i;
            Image img = LoadImage(filePath);
            ImageResize(&img, 100, 100);
            alphabetTextures[i] = LoadTextureFromImage(img);
        }
    }
    void draw()
    {
        for (int i = 0; i < textLength; i++)
        {
            DrawTexture(alphabetTextures[text.at(i) - 48], x+(i*distanceBetweenLetters), y, WHITE);
        }
    }
};