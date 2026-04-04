#include "Menu.h"

Menu::Menu()                                      : Scene { {0.0f}, nullptr   } {}
Menu::Menu(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

Menu::~Menu() { shutdown(); }

void Menu::initialise()
{
   mGameState.nextSceneID = -1;
}

void Menu::update(float deltaTime)
{

   if (IsKeyPressed(KEY_ENTER)) mGameState.nextSceneID = 1;

}

void Menu::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   DrawText("Cool Platformer Game", 20, 20, 30, DARKBLUE);
   DrawText("Press Enter To Play!", 100, 100, 30, DARKBLUE);

}

void Menu::shutdown()
{
   delete mGameState.player;
   delete mGameState.map;

}