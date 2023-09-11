#pragma once
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 700 
#include "raylib.h"
#include "laser.cpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class SpaceShip
{
private:
    //Attributes
    const int velocity = 7;
    const int velocityWhenBoosting = 15;
    const int laserVelocity = 10;
    const int middlePosition = WINDOW_WIDTH/2 - 200;
    char *laserFilePath;
    char side;
    int health = 10;
    int x, y = WINDOW_HEIGHT/2;
    int laserX, laserY;
    int up, down, right, left, shootKey, blastKey;
    int direction;
    int explosionFrameCount = 0;
    int explosionFrame = 0;
    int secondsForRestartingGame = 0;
    bool hasExploded = false;
    bool wasHit;
    bool isBoosting = false;
    bool explosionSoundHasPlayed = false;
    bool hasGameEnded = false;
    Texture2D shipWhenIdle;
    Texture2D shipWhenBoosting[3] 
    {
         
    };
    Texture2D explosion[12] = 
    {

    };
    Sound boostSound;
    Sound movingSoound;
    Sound laserSound;
    Sound hitSound;
    Sound explosionSound;
    vector<Laser> laserList;

    //Private functions
    void checkForLaserColision(vector<Laser> &otherLaserList)
    {
        for (Laser &laser : otherLaserList)
        { 
            if (side == 'l')
            {
                if (laser.getXPos() <= x + 100 && laser.getXPos() >= x - 100 && laser.getYPos() <= y + 50 && laser.getYPos() >= y)
                {
                    laser.setHasHitSomething(true);
                }
            }
            else
            {
                if (laser.getXPos() >= x - 50 && laser.getXPos() <= x + 100 && laser.getYPos() >= y && laser.getYPos() <= y + 50)
                {
                    laser.setHasHitSomething(true);
                }
            }
            if (laser.getHasHitSomething() && !laser.getHasAlreadyHitSomething())
            {
                wasHit = true;
                PlaySound(hitSound);
                health--;
                laser.setHasAlreadyHitSomething(true);
            }
        }
    }
public:
    //Constructors
    SpaceShip(char _side)
    {
        if (_side == 'l')
        {
            side = 'l';
            up = KEY_W;
            down = KEY_S;
            right = KEY_D;
            left = KEY_A;
            shootKey = KEY_L;
            blastKey = KEY_K;
            laserFilePath = "assets/lasers/laser1/laser.png";
            x = 400;
        }
        else
        {
            side = 'r';
            up = KEY_UP;
            down = KEY_DOWN;
            right = KEY_RIGHT;
            left = KEY_LEFT;
            shootKey = KEY_KP_2;
            blastKey = KEY_KP_3;
            laserFilePath = "assets/lasers/laser2/laser.png";
            x = 800;
        }
    }

    SpaceShip(const SpaceShip &spaceShip) = default; 
    
    //Geters
    bool getWasHit()
    {
        return wasHit;
    }
    vector<Laser> &getLaserList()
    {
        return laserList;
    }
    bool getIsDead()
    {
        return hasExploded;
    }
    //Seters
    void setExplosionSound(char *filePath)
    {
        explosionSound = LoadSound(filePath);
    }
    void setBoostSound(char *filePath)
    {
        boostSound = LoadSound(filePath);
    }
    void setLaserSound(char *filePath)
    {
        laserSound = LoadSound(filePath);
    }
    void setHitSound(char *filePath)
    {
        hitSound = LoadSound(filePath);
    }
    void setIdleTexture(char *filePath)
    {
        shipWhenIdle = LoadTexture(filePath);
    }
    void setIdleTextureFromImage(char *imageFilePath)
    {
        Image img = LoadImage(imageFilePath);
        ImageRotateCCW(&img);
        ImageColorTint(&img, BLUE);  
        shipWhenIdle = LoadTextureFromImage(img);
    }
    void setBoostingTextures(char *filePath[3])
    {
        for (int i = 0; i < 3; i++)
        {
            shipWhenBoosting[i] = LoadTexture(filePath[i]);
        }
    }
    void setBoostingTexturesFromImage(char *imageFilePath[3])
    {
        Image img[3] = 
        {
            LoadImage(imageFilePath[0]),
            LoadImage(imageFilePath[1]),
            LoadImage(imageFilePath[2])
        };
        for (int i = 0; i < 3; i++)
        {
            ImageRotateCCW(&img[i]); 
            shipWhenBoosting[i] = LoadTextureFromImage(img[i]);
        }
    }
    void setExplosionTextures(char *filePaths[12])
    {
        for (int i = 0; i < 12; i++)
        {
            explosion[i] = LoadTexture(filePaths[i]);
        }
    }
    //Update functions
    void updateLeft()
    {
        wasHit = false;
        isBoosting = false;
        if (IsKeyDown(left) && x >= 0)
        {
            x -= velocity;
        }
        if (IsKeyDown(right) && x <= middlePosition)
        {
            x += velocityWhenBoosting;
            isBoosting = true;
        }
        if (IsKeyDown(up) && y >= 0)
        {
            y -= velocity;
        }
        if (IsKeyDown(down) && y <= WINDOW_HEIGHT - 100)
        {
            y += velocity;
        }
        if (IsKeyPressed(shootKey))
        {
            Laser *laser = new Laser(this->x + 100, this->y + 20, side);
            laser->setLaserTexture(laserFilePath);
            laserList.push_back(*laser);
            PlaySound(laserSound);
        }
        for (Laser &laser : laserList)
        {
            laser.update(side);
        }
    }
     void updateRight()
    {
        wasHit = false;
        isBoosting = false;
        if (IsKeyDown(left) && x >= middlePosition+200)
        {
            x -= velocityWhenBoosting;;
            isBoosting = true;
        }
        if (IsKeyDown(right) && x <= WINDOW_WIDTH-200)
        {
            x += velocity;
        }
        if (IsKeyDown(up) && y >= 0)
        {
            y -= velocity;
        }
        if (IsKeyDown(down) && y <= WINDOW_HEIGHT - 100)
        {
            y += velocity;
        }
        if (IsKeyPressed(shootKey))
        {
            Laser *laser = new Laser(this->x - 100, this->y + 20, 'r');
            laser->setLaserTexture(laserFilePath);
            laserList.push_back(*laser);
            PlaySound(laserSound);
        }
        for (Laser &laser : laserList)
        {
            laser.update(side);
        }
        
    }
    void update(vector<Laser> &otherLaserList)
    {
        if (health > 0)
        {
            if (side == 'l')
            {
                updateLeft();
                checkForLaserColision(otherLaserList);
            }     
            else
            {
                updateRight();
                checkForLaserColision(otherLaserList);
            }
        }
        else
        {
            secondsForRestartingGame++;
            if (secondsForRestartingGame > 120)
            {
                secondsForRestartingGame = 0;
                explosionFrame = 0;
                health = 10;
                hasExploded = false;
                explosionSoundHasPlayed = false;
                wasHit = false;
            }
        }
            
    }
    void draw()
    {
        if (health <= 0)
        {
            if (!explosionSoundHasPlayed)
            {
                PlaySound(explosionSound);
                explosionSoundHasPlayed = true;
            }
            
            if (!hasExploded)
            {
                DrawTexture(explosion[explosionFrame], x - 150, y - 200, WHITE);
                explosionFrameCount++;
                if (explosionFrameCount % 4 == 0)
                {
                    explosionFrame++;
                }
                if (explosionFrame == 12)
                {
                    hasExploded = true;
                }
            }
        }
        else
        {
            if (isBoosting)
            {
                for (int i = 0; i < 3; i++)
                { 
                    DrawTexture(shipWhenBoosting[i], x, y, WHITE);
                }
            }   
            DrawTexture(shipWhenIdle, x, y, WHITE);
        }        
        for (Laser &laser : laserList)
        {
            laser.draw();
        }
    }
};