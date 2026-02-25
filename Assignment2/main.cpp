/**
* Author: Ian Kreider
* Assignment: Pong Clone
* Date due: [02/28/2026]
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "CS3113/cs3113.h"

enum PlayerControl { CONTROL, AUTOMATIC };

enum BallCount { NONE, ONE, TWO, THREE };

// Global Constants
constexpr int SCREEN_WIDTH  = 1200,
              SCREEN_HEIGHT = 800,
              FPS           = 60;

constexpr Vector2 ORIGIN             = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  P1_BASE_SIZE = { 50.0f, 100.0f },
                  P2_BASE_SIZE   = { 50.0f, 100.0f },
                  P1_INIT_POS  = { 100.0f, ORIGIN.y },
                  P2_INIT_POS    = { SCREEN_WIDTH - 100.0f, ORIGIN.y },

                  BACKGROUND_SIZE = {SCREEN_WIDTH, SCREEN_HEIGHT},

                  GOAL_SIZE = {400.0f, 80.0f},
                  GOAL1_POS = {40.0f, SCREEN_HEIGHT/2},
                  GOAL2_POS = {SCREEN_WIDTH - 40.0f, SCREEN_HEIGHT/2},

                  BALL_SIZE   = { 30.0f, 30.0f },
                  BALL1_INIT_POS  = { ORIGIN.x, ORIGIN.y },
                  BALL2_INIT_POS  = { ORIGIN.x, ORIGIN.y - 50 },
                  BALL3_INIT_POS  = { ORIGIN.x, ORIGIN.y + 50 };                  


constexpr char P1[] = "assets/Goalie.png";
constexpr char P2[]   = "assets/Goalie.png";
constexpr char Ball[]   = "assets/Ball.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gAngle         = 0.0f,
          gPreviousTicks = 0.0f;
          
int       p1Score = 0,
          p2Score = 0;

Vector2 gP1Position = P1_INIT_POS,
        gP1Movement = { 0.0f, 0.0f },
        gP1Scale    = P1_BASE_SIZE,

        gP2Position = P2_INIT_POS,
        gP2Movement = { 0.0f, 0.0f },
        gP2Scale    = P2_BASE_SIZE,

        Ball1Movement = {177.0f, 177.0f},
        gBall1Position = BALL1_INIT_POS,

        Ball2Movement = {-200.0f, 100.0f},
        gBall2Position = BALL2_INIT_POS,

        Ball3Movement = {100.0f, -200.0f},
        gBall3Position = BALL3_INIT_POS,

        gMousePosition = GetMousePosition();

Texture2D gP1Texture;
Texture2D gP2Texture;
Texture2D gBallTexture;
Texture2D background;
Texture2D goal;
Texture2D endscreen;

BallCount balls = ONE;

PlayerControl gPlayerControl = CONTROL;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();


void renderObject(const Texture2D *texture, const Vector2 *position, 
                  const Vector2 *scale, const float angle)
{
    // Whole texture (UV coordinates)
    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(texture->width),
        static_cast<float>(texture->height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        position->x,
        position->y,
        static_cast<float>(scale->x),
        static_cast<float>(scale->y)
    };

    // Origin insidge the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(scale->x) / 2.0f,
        static_cast<float>(scale->y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        *texture, 
        textureArea, destinationArea, originOffset,
        angle, WHITE
    );
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 
        "Pong Game");

    gP1Texture = LoadTexture(P1);
    gP2Texture = LoadTexture(P2);
    gBallTexture = LoadTexture(Ball);
    background = LoadTexture("assets/Grass.jpg");
    goal = LoadTexture("assets/Goal.png");
    endscreen = LoadTexture("assets/Winner.jpg");

    SetTargetFPS(FPS);
}

void processInput() 
{
    gP1Movement.y = 0;
    gP2Movement.y = 0;
    if (IsKeyDown(KEY_W)) gP1Movement.y = -100.0f;
    if (IsKeyDown(KEY_S)) gP1Movement.y = 100.0f;

    if (gPlayerControl == CONTROL) {
        if (IsKeyDown(KEY_UP)) gP2Movement.y = -100.0f;
        if (IsKeyDown(KEY_DOWN)) gP2Movement.y = 100.0f;
    }
    
    if (IsKeyPressed(KEY_T)) {
        if (gPlayerControl == CONTROL) gPlayerControl = AUTOMATIC;
        else gPlayerControl = CONTROL;
    }

    if (IsKeyPressed(KEY_ONE)) balls = ONE; 
    if (IsKeyPressed(KEY_TWO)) balls = TWO; 
    if (IsKeyPressed(KEY_THREE)) balls = THREE; 

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    if (gPlayerControl == AUTOMATIC) {
        if (gP2Position.y > gBall1Position.y) gP2Movement.y = -100.0f;
        else if (gP2Position.y < gBall1Position.y) gP2Movement.y = 100.0f;
    }


    if (balls >= ONE) {
        gP1Position.y += gP1Movement.y * deltaTime;
        if (gP1Position.y < P1_BASE_SIZE.y/2) gP1Position.y = P1_BASE_SIZE.y/2;
        if (gP1Position.y + P1_BASE_SIZE.y/2 > SCREEN_HEIGHT) gP1Position.y = SCREEN_HEIGHT - P1_BASE_SIZE.y/2;

        gP2Position.y += gP2Movement.y * deltaTime;
        if (gP2Position.y < P2_BASE_SIZE.y/2) gP2Position.y = P2_BASE_SIZE.y/2;
        if (gP2Position.y + P2_BASE_SIZE.y/2 > SCREEN_HEIGHT) gP2Position.y = SCREEN_HEIGHT - P2_BASE_SIZE.y/2;

        gBall1Position.x += Ball1Movement.x * deltaTime;
        gBall1Position.y += Ball1Movement.y * deltaTime;

        if (gBall1Position.x > SCREEN_WIDTH-BALL_SIZE.x) {
            Ball1Movement.x *= -1;
            gBall1Position.x = SCREEN_WIDTH-BALL_SIZE.x;
        }
        if (gBall1Position.x < BALL_SIZE.x) {
            Ball1Movement.x *= -1;
            gBall1Position.x = BALL_SIZE.x;
        }

        if (gBall1Position.y > SCREEN_HEIGHT-BALL_SIZE.y) {
            Ball1Movement.y *= -1;
            gBall1Position.y = SCREEN_HEIGHT-BALL_SIZE.y;
        }
        if (gBall1Position.y < BALL_SIZE.y) {
            Ball1Movement.y *= -1;
            gBall1Position.y = BALL_SIZE.y;
        }

        if (gBall1Position.x < gP1Position.x + P1_BASE_SIZE.x/2 &&
            gBall1Position.x > gP1Position.x - P1_BASE_SIZE.x/2 &&
            gBall1Position.y < gP1Position.y + P1_BASE_SIZE.y/2 &&
            gBall1Position.y > gP1Position.y - P1_BASE_SIZE.y/2 &&
            Ball1Movement.x < 0) {
                Ball1Movement.x *= -1;
            }

        if (gBall1Position.x < gP2Position.x + P2_BASE_SIZE.x/2 &&
            gBall1Position.x > gP2Position.x - P2_BASE_SIZE.x/2 &&
            gBall1Position.y < gP2Position.y + P2_BASE_SIZE.y/2 &&
            gBall1Position.y > gP2Position.y - P2_BASE_SIZE.y/2 &&
            Ball1Movement.x > 0) {
                Ball1Movement.x *= -1;
            }

        if (gBall1Position.x < GOAL1_POS.x + GOAL_SIZE.y/2 &&
            gBall1Position.x > GOAL1_POS.x - GOAL_SIZE.y/2 &&
            gBall1Position.y < GOAL1_POS.y + GOAL_SIZE.x/2 &&
            gBall1Position.y > GOAL1_POS.y - GOAL_SIZE.x/2 ) {
                Ball1Movement.x *= -1;
                gBall1Position = ORIGIN;
                p2Score += 1;
            }

        if (gBall1Position.x < GOAL2_POS.x + GOAL_SIZE.y/2 &&
            gBall1Position.x > GOAL2_POS.x - GOAL_SIZE.y/2 &&
            gBall1Position.y < GOAL2_POS.y + GOAL_SIZE.x/2 &&
            gBall1Position.y > GOAL2_POS.y - GOAL_SIZE.x/2 ) {
                Ball1Movement.x *= -1;
                gBall1Position = ORIGIN;
                p1Score += 1;
            }
    }

    if (balls >= TWO) {
        gBall2Position.x += Ball2Movement.x * deltaTime;
        gBall2Position.y += Ball2Movement.y * deltaTime;

        if (gBall2Position.x > SCREEN_WIDTH-BALL_SIZE.x) {
            Ball2Movement.x *= -1;
            gBall2Position.x = SCREEN_WIDTH-BALL_SIZE.x;
        }
        if (gBall2Position.x < BALL_SIZE.x) {
            Ball2Movement.x *= -1;
            gBall2Position.x = BALL_SIZE.x;
        }

        if (gBall2Position.y > SCREEN_HEIGHT-BALL_SIZE.y) {
            Ball2Movement.y *= -1;
            gBall2Position.y = SCREEN_HEIGHT-BALL_SIZE.y;
        }
        if (gBall2Position.y < BALL_SIZE.y) {
            Ball2Movement.y *= -1;
            gBall2Position.y = BALL_SIZE.y;
        }

        if (gBall2Position.x < gP1Position.x + P1_BASE_SIZE.x/2 &&
            gBall2Position.x > gP1Position.x - P1_BASE_SIZE.x/2 &&
            gBall2Position.y < gP1Position.y + P1_BASE_SIZE.y/2 &&
            gBall2Position.y > gP1Position.y - P1_BASE_SIZE.y/2 &&
            Ball2Movement.x < 0) {
                Ball2Movement.x *= -1;
            }

        if (gBall2Position.x < gP2Position.x + P2_BASE_SIZE.x/2 &&
            gBall2Position.x > gP2Position.x - P2_BASE_SIZE.x/2 &&
            gBall2Position.y < gP2Position.y + P2_BASE_SIZE.y/2 &&
            gBall2Position.y > gP2Position.y - P2_BASE_SIZE.y/2 &&
            Ball2Movement.x > 0) {
                Ball2Movement.x *= -1;
            }

        if (gBall2Position.x < GOAL1_POS.x + GOAL_SIZE.y/2 &&
            gBall2Position.x > GOAL1_POS.x - GOAL_SIZE.y/2 &&
            gBall2Position.y < GOAL1_POS.y + GOAL_SIZE.x/2 &&
            gBall2Position.y > GOAL1_POS.y - GOAL_SIZE.x/2 ) {
                Ball2Movement.x *= -1;
                gBall2Position = ORIGIN;
                p2Score += 1;
            }

        if (gBall2Position.x < GOAL2_POS.x + GOAL_SIZE.y/2 &&
            gBall2Position.x > GOAL2_POS.x - GOAL_SIZE.y/2 &&
            gBall2Position.y < GOAL2_POS.y + GOAL_SIZE.x/2 &&
            gBall2Position.y > GOAL2_POS.y - GOAL_SIZE.x/2 ) {
                Ball2Movement.x *= -1;
                gBall2Position = ORIGIN;
                p1Score += 1;
            }
    }

    if (balls >= THREE) {
        gBall3Position.x += Ball3Movement.x * deltaTime;
        gBall3Position.y += Ball3Movement.y * deltaTime;

        if (gBall3Position.x > SCREEN_WIDTH-BALL_SIZE.x) {
            Ball3Movement.x *= -1;
            gBall3Position.x = SCREEN_WIDTH-BALL_SIZE.x;
        }
        if (gBall3Position.x < BALL_SIZE.x) {
            Ball3Movement.x *= -1;
            gBall3Position.x = BALL_SIZE.x;
        }

        if (gBall3Position.y > SCREEN_HEIGHT-BALL_SIZE.y) {
            Ball3Movement.y *= -1;
            gBall3Position.y = SCREEN_HEIGHT-BALL_SIZE.y;
        }
        if (gBall3Position.y < BALL_SIZE.y) {
            Ball3Movement.y *= -1;
            gBall3Position.y = BALL_SIZE.y;
        }

        if (gBall3Position.x < gP1Position.x + P1_BASE_SIZE.x/2 &&
            gBall3Position.x > gP1Position.x - P1_BASE_SIZE.x/2 &&
            gBall3Position.y < gP1Position.y + P1_BASE_SIZE.y/2 &&
            gBall3Position.y > gP1Position.y - P1_BASE_SIZE.y/2 &&
            Ball3Movement.x < 0) {
                Ball3Movement.x *= -1;
            }

        if (gBall3Position.x < gP2Position.x + P2_BASE_SIZE.x/2 &&
            gBall3Position.x > gP2Position.x - P2_BASE_SIZE.x/2 &&
            gBall3Position.y < gP2Position.y + P2_BASE_SIZE.y/2 &&
            gBall3Position.y > gP2Position.y - P2_BASE_SIZE.y/2 &&
            Ball3Movement.x > 0) {
                Ball3Movement.x *= -1;
            }

        if (gBall3Position.x < GOAL1_POS.x + GOAL_SIZE.y/2 &&
            gBall3Position.x > GOAL1_POS.x - GOAL_SIZE.y/2 &&
            gBall3Position.y < GOAL1_POS.y + GOAL_SIZE.x/2 &&
            gBall3Position.y > GOAL1_POS.y - GOAL_SIZE.x/2 ) {
                Ball3Movement.x *= -1;
                gBall3Position = ORIGIN;
                p2Score += 1;
            }

        if (gBall3Position.x < GOAL2_POS.x + GOAL_SIZE.y/2 &&
            gBall3Position.x > GOAL2_POS.x - GOAL_SIZE.y/2 &&
            gBall3Position.y < GOAL2_POS.y + GOAL_SIZE.x/2 &&
            gBall3Position.y > GOAL2_POS.y - GOAL_SIZE.x/2 ) {
                Ball3Movement.x *= -1;
                gBall3Position = ORIGIN;
                p1Score += 1;
            }

    }

    if (p1Score >= 10 || p2Score >= 10) {
        balls = NONE;
    } 


}

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    renderObject(&background, &ORIGIN, &BACKGROUND_SIZE, gAngle);
    


    if (balls >= ONE) {
        DrawText(TextFormat("Score: %i", p1Score), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %i", p2Score), SCREEN_WIDTH-100, 10, 20, WHITE);
        renderObject(&gBallTexture, &gBall1Position, &BALL_SIZE, gAngle);
        if (balls >= TWO) renderObject(&gBallTexture, &gBall2Position, &BALL_SIZE, gAngle);
        if (balls >= THREE) renderObject(&gBallTexture, &gBall3Position, &BALL_SIZE, gAngle);

        // render p1
        renderObject(&gP1Texture, &gP1Position, &gP1Scale, gAngle);

        // render p2
        renderObject(&gP2Texture, &gP2Position, &gP2Scale, gAngle);

        renderObject(&goal, &GOAL1_POS, &GOAL_SIZE, -90);

        renderObject(&goal, &GOAL2_POS, &GOAL_SIZE, 90);
    }

    if (balls == NONE) {
        renderObject(&endscreen, &ORIGIN, &BACKGROUND_SIZE, gAngle);
        if (p1Score>p2Score) DrawText("Player 1 Wins!", SCREEN_WIDTH/2+250, SCREEN_HEIGHT/2, 20, BLACK);
        else DrawText("Player 2 Wins!", SCREEN_WIDTH/2+250, SCREEN_HEIGHT/2, 20, BLACK);
    }

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
    UnloadTexture(gP1Texture);
    UnloadTexture(gP2Texture);
    
    UnloadTexture(gBallTexture);
    UnloadTexture(background);
    UnloadTexture(goal);
    UnloadTexture(endscreen);
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