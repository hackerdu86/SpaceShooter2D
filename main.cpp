#include "include/raylib.h"
#include "font.cpp"
#include "space_ship.cpp"
#include "moon.cpp"
#include "background.cpp"
#include "health_bar.cpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

char *explosionFiles[12] = 
{
    "assets/explosionFrames/1.png", "assets/explosionFrames/2.png", "assets/explosionFrames/3.png", "assets/explosionFrames/4.png", "assets/explosionFrames/5.png", "assets/explosionFrames/6.png", "assets/explosionFrames/7.png", "assets/explosionFrames/8.png", "assets/explosionFrames/9.png", "assets/explosionFrames/10.png", "assets/explosionFrames/11.png", "assets/explosionFrames/12.png"
};
char *hearthFiles[6] =
{
    "assets/hearth/0.png", "assets/hearth/1.png", "assets/hearth/2.png", "assets/hearth/3.png", "assets/hearth/4.png", "assets/hearth/5.png"
};
char *spaceShip1Files[3] = 
{
    "assets/spaceShipFrames/vehicle1/vehicleFrame1.png", "assets/spaceShipFrames/vehicle1/vehicleFrame2.png", "assets/spaceShipFrames/vehicle1/vehicleFrame3.png"
};
char *spaceShip2Files[3] = 
{
    "assets/spaceShipFrames/vehicle2/vehicleFrame1.png", "assets/spaceShipFrames/vehicle2/vehicleFrame2.png", "assets/spaceShipFrames/vehicle2/vehicleFrame3.png"
};

SpaceShip firstSpaceShip('l');
SpaceShip secondSpaceShip('r');
Moon moon = Moon();
Background background = Background();
HealthBar leftBar('l');
HealthBar rightBar('r');
Sound meloTheme = LoadSound("sounds/musics/meloTheme.wav");

bool isGameStarted = false;

void initEntities();
void startGame();
void startMenu();

int main(void)
{
    const int windowWidth = 1400;
    const int windowHeight = windowWidth/2;

    InitWindow(windowWidth, windowHeight, "Space Adventure");
    InitAudioDevice();
    initEntities();
    SetTargetFPS(60); 

    PlaySound(meloTheme);
    while (!WindowShouldClose())
    {
        while (!isGameStarted)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SPACE ADVENTURE", 430, 100, 50, WHITE);
            DrawText("PRESS ENTER TO START", 500, 350, 30, WHITE);
            if (IsKeyPressed(KEY_ENTER)) isGameStarted = true;  
            EndDrawing();
        }
        UnloadSound(meloTheme);
        BeginDrawing();
            startGame();
        EndDrawing();
        
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
void initBars()
{
    leftBar.setHearthTextures(hearthFiles);
    rightBar.setHearthTextures(hearthFiles);
}
void initBackground()
{
    background.setTwoBackgroundTextures("assets/background/blueNebula1.png");
}
void initMoon()
{
    moon.setMoonFrames("assets/moonFrames/");
}
void initShips()
{
    firstSpaceShip.setIdleTexture("assets/spaceShipFrames/vehicle1/vehicleFrame0.png");
    firstSpaceShip.setBoostingTextures(spaceShip1Files);
    firstSpaceShip.setLaserSound("sounds/effects/laserShoot.wav");
    firstSpaceShip.setHitSound("sounds/effects/hitSound.wav");
    firstSpaceShip.setExplosionTextures(explosionFiles);
    firstSpaceShip.setExplosionSound("sounds/effects/explosionSound.wav");
    secondSpaceShip.setIdleTexture("assets/spaceShipFrames/vehicle2/vehicleFrame0.png");
    secondSpaceShip.setBoostingTextures(spaceShip2Files);
    secondSpaceShip.setLaserSound("sounds/effects/laserShoot.wav");
    secondSpaceShip.setHitSound("sounds/effects/hitSound.wav");
    secondSpaceShip.setExplosionTextures(explosionFiles);
    secondSpaceShip.setExplosionSound("sounds/effects/explosionSound.wav");
}
void update()
{
    background.update();
    moon.update();
    firstSpaceShip.update(secondSpaceShip.getLaserList());
    secondSpaceShip.update(firstSpaceShip.getLaserList());
    leftBar.update(firstSpaceShip.getWasHit(), firstSpaceShip.getIsDead());
    rightBar.update(secondSpaceShip.getWasHit(), secondSpaceShip.getIsDead());
}
void draw()
{
    background.draw();
    moon.draw();
    firstSpaceShip.draw();
    secondSpaceShip.draw();
    leftBar.draw();
    rightBar.draw();
}
void initEntities()
{
    initBackground();
    initMoon();
    initShips();
    initBars();
}
void startGame()
{
    update();
    draw();
}