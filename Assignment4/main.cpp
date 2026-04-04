#include "CS3113/Win.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 1000,
              SCREEN_HEIGHT    = 600,
              FPS              = 120,
              NUMBER_OF_LEVELS = 6;

constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
            
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

int playerLives = 3;
Camera2D gCamera = { 0 };

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

Menu *gMenu = nullptr;
Loss *gLoss = nullptr;
Win  *gWin  = nullptr;


LevelA *gLevelA = nullptr;
LevelB *gLevelB = nullptr;
LevelC *gLevelC = nullptr;


// Function Declarations
void switchToScene(Scene *scene);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(Scene *scene)
{
    gCurrentScene = scene;
    gCurrentScene->initialise();
    if (gCurrentScene->getState().player != nullptr) {
        gCamera.target = gCurrentScene->getState().player->getPosition();
    } else {
        gCamera.target = ORIGIN;
    }
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scenes");
    InitAudioDevice();

    gMenu = new Menu(ORIGIN, "#C0897E");

    gLevelA = new LevelA(ORIGIN, "#C0897E");
    gLevelB = new LevelB(ORIGIN, "#011627");
    gLevelC = new LevelC(ORIGIN, "#FFFFFF");

    gLoss = new Loss(ORIGIN, "#000000");
    gWin = new Win(ORIGIN, "#000000");


    gLevels.push_back(gMenu);

    gLevels.push_back(gLevelA);
    gLevels.push_back(gLevelB);
    gLevels.push_back(gLevelC);

    gLevels.push_back(gWin);
    gLevels.push_back(gLoss);


    switchToScene(gLevels[0]);

    gCamera.offset   = ORIGIN;
    gCamera.rotation = 0.0f;
    gCamera.zoom     = 1.0f;

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (IsKeyPressed(KEY_ONE)) switchToScene(gLevels[0]);
    if (IsKeyPressed(KEY_TWO)) switchToScene(gLevels[1]);
    if (IsKeyPressed(KEY_THREE)) switchToScene(gLevels[2]);
    if (IsKeyPressed(KEY_FOUR)) switchToScene(gLevels[3]);
    if (IsKeyPressed(KEY_FIVE)) switchToScene(gLevels[4]);
    if (IsKeyPressed(KEY_SIX)) switchToScene(gLevels[5]);
    
    Entity* player = gCurrentScene->getState().player;

    if (player != nullptr) {
        player->resetMovement();

        if      (IsKeyDown(KEY_A)) player->moveLeft();
        else if (IsKeyDown(KEY_D)) player->moveRight();

        if (IsKeyPressed(KEY_W) && player->isCollidingBottom())
        {
            player->jump();
            PlaySound(gCurrentScene->getState().jumpSound);
        }

        if (GetLength(player->getMovement()) > 1.0f) 
            player->normaliseMovement();

        
    }

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gCurrentScene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;

        if (gCurrentScene->getState().player != nullptr) {
            Vector2 currentPlayerPosition;
            if (gCurrentScene->getState().player->getPosition().y<ORIGIN.y+225.0f) {
                currentPlayerPosition = { 
                    gCurrentScene->getState().player->getPosition().x, 
                    gCurrentScene->getState().player->getPosition().y
                };
            }
            else {
                currentPlayerPosition = { 
                    gCurrentScene->getState().player->getPosition().x, 
                    ORIGIN.y+225.0f
                };
            }
            panCamera(&gCamera, &currentPlayerPosition);
        }

        if (gCurrentScene->getDie() == true) {
            playerLives -= 1;
            PlaySound(gCurrentScene->getState().dieSound);
            gCurrentScene->restart();
        }

        if (playerLives == 0) {
            switchToScene(gLevels[5]);
        }

        if (gCurrentScene == gLoss || gCurrentScene == gWin) {
            playerLives = 3;
        }
    }
}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);

    gCurrentScene->render();

    EndMode2D();
    EndDrawing();
}

void shutdown() 
{
    delete gLevelA;
    delete gLevelB;
    delete gLevelC;
    
    delete gMenu;
    delete gLoss;

    for (int i = 0; i < NUMBER_OF_LEVELS; i++) gLevels[i] = nullptr;

    CloseAudioDevice();
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();

        if (gCurrentScene->getState().nextSceneID >= 0)
        {
            int id = gCurrentScene->getState().nextSceneID;
            switchToScene(gLevels[id]);
        }

        render();
    }

    shutdown();

    return 0;
}