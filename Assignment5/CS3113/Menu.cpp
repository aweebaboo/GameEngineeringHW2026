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

   DrawText("Cool Top Down RPG Game", 150, 20, 50, WHITE);
   DrawText("  Press WASD to move!", 150, 100, 50, WHITE);
   DrawText("  Press E to interact!", 150, 180, 50, WHITE);
   DrawText("  Press Enter To Play!", 150, 260, 50, WHITE);


}

void Menu::shutdown()
{

}