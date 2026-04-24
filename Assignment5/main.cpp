#include "CS3113/ShaderProgram.h"

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

int playerHP = 5;
Camera2D gCamera = { 0 };

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

Menu *gMenu = nullptr;
Loss *gLoss = nullptr;
Win  *gWin  = nullptr;


LevelA *gLevelA = nullptr;
LevelB *gLevelB = nullptr;
LevelC *gLevelC = nullptr;
LevelD *gLevelD = nullptr;

ShaderProgram gShader;
Vector2 gLightPosition = { 0.0f, 0.0f };

Sound win;
Sound lose;



// Function Declarations
void switchToScene(Scene *scene);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(Scene *scene)
{
    if (gCurrentScene != nullptr) {
        gCurrentScene->shutdown();
    }
    
    gCurrentScene = scene;
    gCurrentScene->initialise();
    gCurrentScene->setplayerHP(&playerHP);

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

    win = LoadSound("assets/game/win.mp3");
    lose = LoadSound("assets/game/Failure.mp3");

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gMenu = new Menu(ORIGIN, "#000000");

    gLevelA = new LevelA(ORIGIN, "#000000");
    gLevelB = new LevelB(ORIGIN, "#000000");
    gLevelC = new LevelC(ORIGIN, "#000000");
    gLevelD = new LevelD(ORIGIN, "#000000");

    gLoss = new Loss(ORIGIN, "#000000");
    gWin = new Win(ORIGIN, "#000000");


    gLevels.push_back(gMenu);

    gLevels.push_back(gLevelA);
    gLevels.push_back(gLevelB);
    gLevels.push_back(gLevelC);
    gLevels.push_back(gLevelD);

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

    

    if (player != nullptr && !gCurrentScene->getDialogueActive()) {
        player->resetMovement();

        if      (IsKeyDown(KEY_A)) {
            if (player->isCollidingLeft() != true) player->moveLeft();
        }
        else if (IsKeyDown(KEY_D)) {
            if (player->isCollidingRight() != true) player->moveRight();
        }
        if      (IsKeyDown(KEY_W)) {
            if (player->isCollidingTop() != true) player->moveUp();
        }
        else if (IsKeyDown(KEY_S)) {
            if (player->isCollidingBottom() != true) player->moveDown();
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
            float xPos;
            float yPos;

            Vector2 bounds = gCurrentScene->getCameraLimits();

            if (gCurrentScene->getState().player->getPosition().y>ORIGIN.y+bounds.y) {
                yPos = ORIGIN.y+bounds.y;
            }
            else if (gCurrentScene->getState().player->getPosition().y<ORIGIN.y-bounds.y) {
                yPos = ORIGIN.y-bounds.y;
            } 
            else {
                yPos = gCurrentScene->getState().player->getPosition().y;
            }

            if (gCurrentScene->getState().player->getPosition().x>ORIGIN.x+bounds.x) {
                xPos = ORIGIN.x+bounds.x;
            }
            else if (gCurrentScene->getState().player->getPosition().x<ORIGIN.x-bounds.x) {
                xPos = ORIGIN.x-bounds.x;
            } 
            else {
                xPos = gCurrentScene->getState().player->getPosition().x;
            }

            currentPlayerPosition = {xPos, yPos};

            gLightPosition = gCurrentScene->getState().player->getPosition();
            panCamera(&gCamera, &currentPlayerPosition);
        }

        if (gCurrentScene->getDie() == true) {
            PlaySound(lose);
            switchToScene(gLevels[6]);
        }

        if (gCurrentScene == gLoss || gCurrentScene == gWin) {
            playerHP = 5;
        }
    }

}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);
    gShader.begin();

    gCurrentScene->render();
    gShader.setVector2("lightPosition", gLightPosition);

    gShader.end();

    EndMode2D();

    if (gCurrentScene->getState().player != nullptr)
    {
        DrawText(
            TextFormat("HP: %d", *gCurrentScene->getState().playerHP),
            20, 20, 30, RED
        );
    }

    if (gCurrentScene->getDialogueActive())
    {
        const DialogueLine* line = gCurrentScene->getCurrentDialogueLine();
        if (line != nullptr)
        {
            const int BOX_X = 100, BOX_Y = 430,
                      BOX_W = 800, BOX_H = 130;

            DrawRectangle(BOX_X, BOX_Y, BOX_W, BOX_H, BLACK);
            DrawRectangleLines(BOX_X, BOX_Y, BOX_W, BOX_H, WHITE);
            DrawText(line->speaker, BOX_X + 16, BOX_Y + 10, 20, YELLOW);
            DrawText(line->text,    BOX_X + 16, BOX_Y + 40, 20, WHITE);
            DrawText("[ SPACE ] Continue",
                BOX_X + BOX_W - 180, BOX_Y + BOX_H - 25, 16, GRAY);
        }
    }

    EndDrawing();
}

void shutdown() 
{
    delete gLevelA;
    delete gLevelB;
    delete gLevelC;
    delete gLevelD;
    
    delete gMenu;
    delete gLoss;

    gShader.unload();

   UnloadSound(win);
   UnloadSound(lose);


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
            if (id == 1 || id == 3 || id == 4) {
                gShader.setInt("lighton", 1);
            }
            else gShader.setInt("lighton", 0);
            if (gCurrentScene == gWin) {
                PlaySound(win);
            }
        }

        render();
    }

    shutdown();

    return 0;
}