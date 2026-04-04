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
   DrawText("You Win! Enter to play again!", 200, 200, 30, RAYWHITE);
}

void Win::shutdown()
{
   delete mGameState.player;
   delete mGameState.map;
}