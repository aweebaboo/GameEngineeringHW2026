#include "LevelC.h"

LevelC::LevelC()                                      : Scene { {0.0f}, nullptr   } {}
LevelC::LevelC(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelC::~LevelC() { shutdown(); }

void LevelC::restart() {
   mGameState.player->setPosition({mOrigin.x - 625.0f, mOrigin.y});
   mGameState.playerDie = false;
   mGameState.player->setDead(false);
   mGameState.enemy->setPosition({mOrigin.x - 1200.0f, mOrigin.y});
}

void LevelC::initialise()
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

   mGameState.player = new Entity(
      {mOrigin.x - 625.0f, mOrigin.y}, // position
      {70, 70},             // scale
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

   mGameState.enemy = new Entity(
      {mOrigin.x - 1200.0f, mOrigin.y}, // position
      {75, 75},             // scale
      "assets/game/ghost.png",
      NPC
   );
   mGameState.enemy->setAIType(LERPER);
   mGameState.enemy->setAIState(IDLE);


   mGameState.win = new Entity(
      {mOrigin.x - 625.0f, mOrigin.y-375.0f}, // position
      {75, 75},             // scale
      "assets/game/win.png",                   // texture file address
      WIN                                   // entity type
   );
}

void LevelC::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   mGameState.player->update(
      deltaTime,      // delta time / fixed timestep
      nullptr,        // player
      mGameState.map, // map
      mGameState.enemy,        // collidable entities
      1,              // col. entity count
      mGameState.win
   );

   mGameState.enemy->update(
      deltaTime,         // delta time
      mGameState.player, // target for AI
      mGameState.map,    // map for collisions
      nullptr,           // no additional collidable entities
      0,                 // collision count
      nullptr            // no win entity
   );

   if (mGameState.player->getWin()) 
      {PlaySound(mGameState.winSound); 
      mGameState.nextSceneID = 4;}
   
   if (mGameState.enemy->isCollidingLeft() && mGameState.enemy->getMovement().x < 0.0f
    && mGameState.enemy->isCollidingBottom()) {
      mGameState.enemy->jump();
   }

   if (mGameState.enemy->isCollidingRight() && mGameState.enemy->getMovement().x > 0.0f
    && mGameState.enemy->isCollidingBottom()) {
      mGameState.enemy->jump();
   }
      
   if (mGameState.player->getPosition().y > 1000 || 
       mGameState.player->isDead()) mGameState.playerDie = true;

   if (IsKeyPressed(KEY_F)) mGameState.playerDie = true;

}

void LevelC::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.player->render();
   mGameState.map->render();
   mGameState.win->render();
   mGameState.enemy->render();
}

void LevelC::shutdown()
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