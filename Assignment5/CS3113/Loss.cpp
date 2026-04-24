#include "Loss.h"

Loss::Loss()                                      : Scene { {0.0f}, nullptr   } {}
Loss::Loss(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

Loss::~Loss() { shutdown(); }

void Loss::initialise()
{
   mGameState.nextSceneID = -1;
}

void Loss::update(float deltaTime)
{

   if (IsKeyPressed(KEY_ENTER)) mGameState.nextSceneID = 0;

}

void Loss::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   DrawText("You died. Press enter to try again!", 200, 200, 30, RAYWHITE);
}

void Loss::shutdown()
{
   
}