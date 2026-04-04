#include "LevelA.h"

LevelA::LevelA()                                      : Scene { {0.0f}, nullptr   } {}
LevelA::LevelA(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelA::~LevelA() { shutdown(); }

void LevelA::restart() {
   mGameState.player->setPosition({mOrigin.x - 625.0f, mOrigin.y});
   mGameState.playerDie = false;
   mGameState.player->setDead(false);
   mGameState.enemy->setPosition({1125.0f, 500.0f});
}

void LevelA::initialise()
{
   mGameState.nextSceneID = -1;

   mGameState.bgm = LoadMusicStream("assets/game/music.mp3");
   mGameState.bgm.looping = true;
   SetMusicVolume(mGameState.bgm, 0.05f);
   PlayMusicStream(mGameState.bgm);

   mGameState.jumpSound = LoadSound("assets/game/jump.mp3");

   mGameState.winSound = LoadSound("assets/game/win.mp3");

   mGameState.dieSound = LoadSound("assets/game/die.mp3");

   /*
      ----------- MAP -----------
   */
   mGameState.map = new Map(
      LEVEL_WIDTH, LEVEL_HEIGHT,   // map grid cols & rows
      (unsigned int *) mLevelData, // grid data
      "assets/game/tilemap_packed.png",   // texture filepath
      TILE_DIMENSION,              // tile size
      15, 10,                        // texture cols & rows
      mOrigin                      // in-game origin
   );

   /*
      ----------- PROTAGONIST -----------
   */
   std::map<Direction, std::vector<int>> playerAnimationAtlas = {
      {DOWN,  { 12 }},
      {LEFT,  { 17,16,15,14 }},
      {UP,    { 12 }},
      {RIGHT, { 14,15,16,17 }},
   };
   float sizeRatio  = 48.0f / 64.0f;

   // Assets from @see https://sscary.itch.io/the-adventurer-female
   mGameState.player = new Entity(
      {mOrigin.x - 625.0f, mOrigin.y}, // position
      {75, 75},             // scale
      "assets/game/test.png",                   // texture file address
      ATLAS,                                    // single image or atlas?
      { 7, 7 },                                 // atlas dimensions
      playerAnimationAtlas,                    // actual atlas
      PLAYER                                    // entity type
   );

   
   mGameState.player->setPosition({mOrigin.x - 625.0f, mOrigin.y});
   
   mGameState.player->setJumpingPower(550.0f);
   mGameState.player->setColliderDimensions({
      mGameState.player->getScale().x / 1.5f,
      mGameState.player->getScale().y / 1.3f
   });
   mGameState.player->setAcceleration({0.0f, ACCELERATION_OF_GRAVITY});

   mGameState.player->setWin(false);


   mGameState.player->setJumpingPower(550.0f);

   mGameState.enemy = new Entity(
      {1125.0f, 500.0f}, // position
      {75, 75},             // scale
      "assets/game/enemy.png",
      NPC
   );

   mGameState.enemy->setAIType(WANDERER);
   mGameState.enemy->setSpeed(100);
   mGameState.enemy->setAcceleration({0.0f, ACCELERATION_OF_GRAVITY});
   mGameState.enemy->setJumpingPower(550.0f);  


   mGameState.win = new Entity(
      {1125.0f, 425.0f}, // position
      {75, 75},             // scale
      "assets/game/win.png",                   // texture file address
      WIN                                   // entity type
   );
}

void LevelA::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   mGameState.player->update(
      deltaTime,      // delta time / fixed timestep
      nullptr,        // player
      mGameState.map, // map
      mGameState.enemy,        // collidable entities
      1,              // col. entity count
      mGameState.win // win entity
   );

   mGameState.enemy->update(
      deltaTime,         
      mGameState.player, 
      mGameState.map,    
      nullptr,           
      0,                 
      nullptr            
   );

   if (mGameState.enemy->isCollidingLeft() && mGameState.enemy->getMovement().x < 0.0f
    && mGameState.enemy->isCollidingBottom()) {
      mGameState.enemy->jump();
   }

   if (mGameState.enemy->isCollidingRight() && mGameState.enemy->getMovement().x > 0.0f
    && mGameState.enemy->isCollidingBottom()) {
      mGameState.enemy->jump();
   }

   if (mGameState.player->getWin()) 
      {PlaySound(mGameState.winSound); 
      mGameState.nextSceneID = 2;}
   if (mGameState.player->getPosition().y > 1000 || 
       mGameState.player->isDead()) mGameState.playerDie = true;
   
   if (IsKeyPressed(KEY_F)) mGameState.playerDie = true;

}

void LevelA::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.player->render();
   mGameState.map->render();
   mGameState.win->render();
   mGameState.enemy->render();
}

void LevelA::shutdown()
{
   delete mGameState.player;
   delete mGameState.map;
   delete mGameState.enemy;
   delete mGameState.win;

   UnloadMusicStream(mGameState.bgm);
   UnloadSound(mGameState.jumpSound);
   UnloadSound(mGameState.winSound);
   UnloadSound(mGameState.dieSound);
}