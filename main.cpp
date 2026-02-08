/**

* Author: Ian Kreider

* Assignment: Simple 2D Scene

* Date due: [2/14/2026]

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "CS3113/cs3113.h"
#include <math.h>

// Global Constants
constexpr int   SCREEN_WIDTH  = 1600,
                SCREEN_HEIGHT = 900,
                FPS           = 60,
                SIZE          = 1000;
constexpr float MAX_AMP       = 40.0f;

constexpr char    BG_COLOUR[] = "#B2AAC6";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

constexpr Vector2 IMG1_SIZE   = {  300.0f, 200.0f };
constexpr Vector2 IMG2_SIZE   = {  120.0f, 120.0f };
constexpr Vector2 IMG3_SIZE   = {  300.0f, 250.0f };

constexpr char img1[]  = "cat.jpg";
constexpr char img2[]  = "mouse.jpg";
constexpr char img3[]  = "person.jpg";


// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gScaleFactor   = SIZE ,
          gAngle         = 0.0f,
          gPulseTime     = 0.0f;
Vector2   gPosition1      = ORIGIN;
Vector2   gPosition2      = ORIGIN;

Vector2   gPosition3      = {150,100};

Vector2   gScale1         = IMG1_SIZE;
Vector2   gScale2         = IMG2_SIZE;
Vector2   gScale3         = IMG3_SIZE;



float     gPreviousTicks = 0.0f;
float angle1 = 0.0f;
float angle2 = 0.0f;
float angle3 = 0.0f;



float gRotX = 0.0f;
float gRotY = 0.0f;

Texture2D gTexture1;
Texture2D gTexture2;
Texture2D gTexture3;


// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    gTexture1 = LoadTexture(img1);
    gTexture2 = LoadTexture(img2);
    gTexture3 = LoadTexture(img3);


    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    angle1 += deltaTime * 180;

    gPulseTime += 1.0f * deltaTime;

    gScale1 = {
        IMG1_SIZE.x + MAX_AMP * cos(gPulseTime),
        IMG1_SIZE.y + MAX_AMP * cos(gPulseTime)
    };

    gPosition1.x = ORIGIN.x + 200*(cos(gPulseTime));
    gPosition1.y = ORIGIN.y + 200*(sin(gPulseTime));

    gPosition2.x = gPosition1.x + 300*(cos(gPulseTime*1.5));
    gPosition2.y = gPosition1.y + 300*(sin(gPulseTime*1.5));
}

void render()
{
    BeginDrawing();

    unsigned char r = (unsigned char)(127 + 127 * sin(gPulseTime));
    unsigned char g = (unsigned char)(127 + 127 * sin(gPulseTime + 2.0f));
    unsigned char b = (unsigned char)(127 + 127 * sin(gPulseTime + 4.0f));

    Color dynamicBG = { r, g, b, 255 };

    ClearBackground(dynamicBG);

    // Whole texture (UV coordinates)
    Rectangle textureArea1 = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTexture1.width),
        static_cast<float>(gTexture1.height)
    };

    Rectangle textureArea2 = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTexture2.width),
        static_cast<float>(gTexture2.height)
    };

    Rectangle textureArea3 = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTexture3.width),
        static_cast<float>(gTexture3.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea1 = {
        gPosition1.x,
        gPosition1.y,
        static_cast<float>(gScale1.x),
        static_cast<float>(gScale1.y)
    };

    Rectangle destinationArea2 = {
        gPosition2.x,
        gPosition2.y,
        static_cast<float>(gScale2.x),
        static_cast<float>(gScale2.y)
    };

    Rectangle destinationArea3 = {
        gPosition3.x,
        gPosition3.y,
        static_cast<float>(gScale3.x),
        static_cast<float>(gScale3.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 objectOrigin1 = {
        static_cast<float>(gScale1.x) / 2.0f,
        static_cast<float>(gScale1.y) / 2.0f
    };

    Vector2 objectOrigin2 = {
        static_cast<float>(gScale2.x) / 2.0f,
        static_cast<float>(gScale2.y) / 2.0f
    };

    Vector2 objectOrigin3 = {
        static_cast<float>(gScale3.x) / 2.0f,
        static_cast<float>(gScale3.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTexture1, 
        textureArea1, 
        destinationArea1, 
        objectOrigin1, 
        angle1, 
        WHITE
    );

    DrawTexturePro(
        gTexture2, 
        textureArea2, 
        destinationArea2, 
        objectOrigin2, 
        angle2, 
        WHITE
    );

    DrawTexturePro(
        gTexture3, 
        textureArea3, 
        destinationArea3, 
        objectOrigin3, 
        angle3, 
        WHITE
    );

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow(); 
    UnloadTexture(gTexture1);
    UnloadTexture(gTexture2);
    UnloadTexture(gTexture3);
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