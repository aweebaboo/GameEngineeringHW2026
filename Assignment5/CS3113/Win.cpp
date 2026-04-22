#include "Win.h"

Win::Win()                                      : Scene { {0.0f}, nullptr   } {}
Win::Win(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

Win::~Win() { shutdown(); }

void Win::initialise()
{
   mGameState.nextSceneID = -1;
   
}

void Win::update(float deltaTime)
{

   if (IsKeyPressed(KEY_ENTER)) mGameState.nextSceneID = 0;
}

void Win::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));
   DrawText("Apparently the evil king was really weak.", 50, 100, 30, RAYWHITE);
   DrawText("You took his treasure after killing him", 50, 150, 30, RAYWHITE);
   DrawText("Hopefully the monsters die out quickly", 50, 200, 30, RAYWHITE);
   DrawText("You Win! Enter to play again!", 50, 250, 40, RAYWHITE);
}

void Win::shutdown()
{

}