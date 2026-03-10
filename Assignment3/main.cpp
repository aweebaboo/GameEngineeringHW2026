/**
* Author: Ian Kreider
* Assignment: Lunar Lander
* Date due: 5/14/2026
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "CS3113/Entity.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1000,
              SCREEN_HEIGHT = 600,
              FPS           = 120;

constexpr char BG_COLOUR[]    = "#C0897E";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

constexpr int   NUMBER_OF_ASTEROIDS   = 10;
constexpr float TILE_DIMENSION          = 50.0f,
                // in m/ms², since delta time is in ms
                ACCELERATION_OF_GRAVITY = 50.0f,
                FIXED_TIMESTEP          = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Entity *gPlayer = nullptr;

Entity *gAsteroids = nullptr;

Entity *gPlatforms = nullptr;
Entity *gWin       = nullptr;

Entity *gExplosion = nullptr;

constexpr int NUMBER_OF_PLATFORMS = 3;

enum PlayStatus { PLAYING, LOSS, WIN };

float gExplosionTimer = 0.0f;
constexpr float EXPLOSION_DURATION = 0.6f;

Entity *gMovingAsteroid = nullptr;
float gMovingAsteroidDir = 1.0f;

PlayStatus gPlayStatus = PLAYING;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lunar Lander");

    gPlayer = new Entity(
        { 80.0f, 530.0f },
        { 40.0f, 40.0f },
        "assets/lander.png"
    );
    gPlayer->setEntityType(PLAYER);
    gPlayer->setFuel(100.0f);
    gPlayer->setPower(100.0f);
    gPlayer->setFuelUse(0.1f);
    gPlayer->setGravity(ACCELERATION_OF_GRAVITY);

    gExplosion = new Entity(
        { 0.0f, 0.0f },
        { 80.0f, 80.0f },
        "assets/explosion.png",
        ATLAS,
        { 1,8 },
        { { RIGHT, { 0, 1, 2, 3, 4, 5, 6, 7, 8 } } }
    );

    gExplosion->deactivate();
    gExplosion->setFrameSpeed(8);

    gWin = new Entity(
        { 920.0f, 60.0f },
        { 60.0f, 60.0f },
        "assets/win.png"
    );
    gWin->setEntityType(PLATFORM);
    gWin->setColliderDimensions({ 60.0f, 60.0f });

    gPlatforms = new Entity[NUMBER_OF_PLATFORMS];

    gPlatforms[0].setTexture("assets/platform.png");
    gPlatforms[0].setScale({ 160.0f, 20.0f });
    gPlatforms[0].setColliderDimensions({ 160.0f, 20.0f });
    gPlatforms[0].setPosition({ 80.0f, 570.0f });
    gPlatforms[0].setEntityType(PLATFORM);

    gPlatforms[1].setTexture("assets/platform.png");
    gPlatforms[1].setScale({ 120.0f, 20.0f });
    gPlatforms[1].setColliderDimensions({ 120.0f, 20.0f });
    gPlatforms[1].setPosition({ 500.0f, 380.0f });
    gPlatforms[1].setEntityType(PLATFORM);

    gPlatforms[2].setTexture("assets/platform.png");
    gPlatforms[2].setScale({ 120.0f, 20.0f });
    gPlatforms[2].setColliderDimensions({ 120.0f, 20.0f });
    gPlatforms[2].setPosition({ 800.0f, 200.0f });
    gPlatforms[2].setEntityType(PLATFORM);

    gAsteroids = new Entity[NUMBER_OF_ASTEROIDS];

    Vector2 asteroidPositions[NUMBER_OF_ASTEROIDS] = {
        { 200.0f, 480.0f },
        { 200.0f, 400.0f },
        { 300.0f, 300.0f },
        { 300.0f, 180.0f },
        { 300.0f,  80.0f },
        { 500.0f, 480.0f },
        { 500.0f, 320.0f },
        { 700.0f, 400.0f },
        { 700.0f, 260.0f },
        { 700.0f, 140.0f },
    };

    gMovingAsteroid = new Entity(
        { 450.0f, 300.0f },
        { 40.0f, 40.0f },
        "assets/asteroid.png"
    );
    gMovingAsteroid->setEntityType(FAIL);
    gMovingAsteroid->setColliderDimensions({ 34.0f, 34.0f });

    for (int i = 0; i < NUMBER_OF_ASTEROIDS; i++)
    {
        gAsteroids[i].setTexture("assets/asteroid.png");
        gAsteroids[i].setEntityType(FAIL);
        gAsteroids[i].setScale({ 40.0f, 40.0f });
        gAsteroids[i].setColliderDimensions({ 34.0f, 34.0f });
        gAsteroids[i].setPosition(asteroidPositions[i]);
    }

    SetTargetFPS(FPS);
}


void processInput()
{
    if (gPlayStatus == PLAYING) {
        if (IsKeyDown(KEY_LEFT))  gPlayer->turn(-90.0f * FIXED_TIMESTEP);
        if (IsKeyDown(KEY_RIGHT)) gPlayer->turn( 90.0f * FIXED_TIMESTEP);
        
        if (IsKeyDown(KEY_SPACE)) gPlayer->setBoosting(true);
        else {
            gPlayer->setBoosting(false);
            gPlayer->setAcceleration({ 0.0f, ACCELERATION_OF_GRAVITY });
        }
    }

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    float ticks     = (float)GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    deltaTime += gTimeAccumulator;
    if (deltaTime < FIXED_TIMESTEP) { gTimeAccumulator = deltaTime; return; }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        if (gPlayStatus == PLAYING)
        {

            Vector2 pos = gMovingAsteroid->getPosition();
            pos.y += 120.0f * gMovingAsteroidDir * FIXED_TIMESTEP;

            if (pos.y > SCREEN_HEIGHT - 20.0f || pos.y < 20.0f)
                gMovingAsteroidDir *= -1.0f;

            gMovingAsteroid->setPosition(pos);

            gPlayer->update(FIXED_TIMESTEP, gAsteroids, NUMBER_OF_ASTEROIDS);
            gPlayer->update(FIXED_TIMESTEP, gPlatforms, NUMBER_OF_PLATFORMS);
            gPlayer->update(FIXED_TIMESTEP, gMovingAsteroid, 1);

        }

        if (gPlayStatus == LOSS && gExplosion->isActive())
        {
            gExplosionTimer += FIXED_TIMESTEP;
            gExplosion->update(FIXED_TIMESTEP, nullptr, 0);
            if (gExplosionTimer >= EXPLOSION_DURATION)
                gExplosion->deactivate();
        }

        deltaTime -= FIXED_TIMESTEP;
    }

    gTimeAccumulator = deltaTime;

    if (!gPlayer->isActive() && gPlayStatus == PLAYING)
    {
        gPlayStatus = LOSS;
        gExplosion->setPosition(gPlayer->getPosition());
        gExplosion->activate();
    }

    if (gPlayer->isActive() && gWin->isActive())
    {
        Entity *e = gWin;
        float xDist = fabs(gPlayer->getPosition().x - e->getPosition().x) -
                    ((gPlayer->getColliderDimensions().x + e->getColliderDimensions().x) / 2.0f);
        float yDist = fabs(gPlayer->getPosition().y - e->getPosition().y) -
                    ((gPlayer->getColliderDimensions().y + e->getColliderDimensions().y) / 2.0f);
        if (xDist < 0.0f && yDist < 0.0f) gPlayStatus = WIN;
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    if (gPlayStatus == PLAYING) {
        for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) gPlatforms[i].render();
        for (int i = 0; i < NUMBER_OF_ASTEROIDS; i++) gAsteroids[i].render();
        gMovingAsteroid->render();
        gWin->render();
        gPlayer->render();
        gPlayer->displayFuel();
    }

    gExplosion->render();

    if (gPlayStatus == LOSS && !gExplosion->isActive())
        DrawText("You crashed!", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2, 30, RED);
    else if (gPlayStatus == WIN)
        DrawText("You landed!", SCREEN_WIDTH / 2 - 55, SCREEN_HEIGHT / 2, 30, GREEN);

    EndDrawing();
}

    
void shutdown()
{
    delete   gPlayer;
    delete   gWin;
    delete[] gPlatforms;
    delete[] gAsteroids;
    delete gExplosion;
    delete gMovingAsteroid;
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}