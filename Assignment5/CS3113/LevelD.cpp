#include "LevelD.h"

LevelD::LevelD()                                      : Scene { {0.0f}, nullptr   } {}
LevelD::LevelD(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelD::~LevelD() { shutdown(); }

void LevelD::initialise()
{
   mBreakableCount = 0;
   mEnemyCount = 0;
   mPickupCount = 0;
   mLeverCount = 0;
   levers_pulled = 0;
   mDialogueCount = 0;
   mDialogueIndex = 0;

   mGameState.playerDie = false;
   
   mGameState.nextSceneID = -1;

   mGameState.bgm = LoadMusicStream("assets/game/Chaos King.mp3");
   mGameState.bgm.looping = true;
   SetMusicVolume(mGameState.bgm, 0.3f);
   PlayMusicStream(mGameState.bgm);

   mGameState.jumpSound = LoadSound("assets/game/jump.mp3");

   mGameState.winSound = LoadSound("assets/game/win.mp3");

   mGameState.dieSound = LoadSound("assets/game/die.mp3");

   swordHit = LoadSound("assets/game/swordhit.mp3");
   SetSoundVolume(swordHit, 0.25);

   dialogue = LoadSound("assets/game/dialogue.mp3");
   SetSoundVolume(dialogue, 0.25);

   playerHurt = LoadSound("assets/game/playerhurt.mp3");
   SetSoundVolume(swordHit, 0.25);

   enemyDie = LoadSound("assets/game/enemydie.mp3");
   SetSoundVolume(dialogue, 0.25);

   /*
      ----------- MAP -----------
   */
   mGameState.collisionMap = new Map(
      LEVELD_WIDTH, LEVELD_HEIGHT,   // map grid cols & rows
      (unsigned int *) mCollisionData, // grid data
      "assets/game/tilemap_packed.png",   // texture filepath
      TILE_DIMENSION,              // tile size
      15, 10,                        // texture cols & rows
      mOrigin                      // in-game origin
   );

   mGameState.visualMap = new Map(
      LEVELD_WIDTH, LEVELD_HEIGHT,
      (unsigned int *) mVisualData,
      "assets/game/dungeon.png",
      TILE_DIMENSION,
      32, 24,
      mOrigin
   );

   /*
      ----------- PROTAGONIST -----------
   */
   std::map<Direction, std::vector<int>> playerAnimationAtlas = {
      {DOWN,  {  16,17,18,19  }},
      {LEFT,  { 20,21,22,23 }},
      {UP,    {  28,29,30,31  }},
      {RIGHT, { 24,25,26,27 }},
   };
   float sizeRatio  = 48.0f / 64.0f;

   mGameState.player = new Entity(
      {mOrigin.x, mOrigin.y+300.0f}, // position
      {96, 96},             // scale
      "assets/game/hero.png",                   // texture file address
      ATLAS,                                    // single image or atlas?
      { 8, 4 },                                 // atlas dimensions
      playerAnimationAtlas,                    // actual atlas
      PLAYER                                    // entity type
   );

   mGameState.player->setColliderDimensions({
      42.0f,
      58.0f
   });

   mGameState.player->resetMovement();

   //enemy stuff

   mEnemyCount = 1;

   mEnemies[0] = new Entity(
      { mOrigin.x, mOrigin.y },
      { 64.0f, 64.0f },
      "assets/game/evilking.png",
      ENEMY
   );

   mEnemies[0]->setAIType(KING);
   mEnemies[0]->setAIState(IDLE);
   mEnemies[0]->setEnemyHP(1);
   mEnemies[0]->setSpeed(0);


   //obstacle stuff
   // mBreakableCount = 3;

   // mBreakables[0] = new Entity(
   //    { mOrigin.x - 64.0f, mOrigin.y - 256.0f },
   //    { 64.0f, 64.0f },
   //    "assets/game/obstacle.png",
   //    BREAKABLE
   // );

   // mBreakables[1] = new Entity(
   //    { mOrigin.x, mOrigin.y - 256.0f },
   //    { 64.0f, 64.0f },
   //    "assets/game/obstacle.png",
   //    BREAKABLE
   // );

   // mBreakables[2] = new Entity(
   //    { mOrigin.x + 64.0f, mOrigin.y - 256.0f },
   //    { 64.0f, 64.0f },
   //    "assets/game/obstacle.png",
   //    BREAKABLE
   // );

   //door stuff
   mGameState.door = new Entity(
      { -1000, -1000 },
      { 64.0f, 64.0f },
      "assets/game/win.png",
      DOOR
   );


   //sword stuff

   mGameState.sword = new Entity(
      {mGameState.player->getPosition().x, mGameState.player->getPosition().y},
      {25, 64},           
      "assets/game/sword.png", 
      SWORD                  
   );

   for (int i = 0; i < GameState::MAX_PROJECTILES; i++)
   {
      mGameState.projectiles[i] = new Entity(
         {0.0f, 0.0f},
         {40, 40},
         "assets/game/arrow.png",
         PROJECTILE
      );
      mGameState.projectiles[i]->deactivate();
   }

   mGameState.sign = new Entity(
      {-3000, -3000},
      {48, 64},             
      "assets/game/sign.png",
      DIALOGUE
   );

   mDialogueLines[0] = { "Evil King", "So, you have finally made your way to me." };
   mDialogueLines[1] = { "Evil King", "Well it's too late, you'll never stop me!" };
   mDialogueLines[2] = { "Evil King", "There is nothing that can stand in the way of my evil plans!" };
   mDialogueCount = 3;

   // mLevers[0] = new Entity(
   //    {-400.0f, 450.0f},
   //    {64, 64},
   //    "assets/game/lever.png",
   //    INTERACTABLE
   // );

   // mLevers[1] = new Entity(
   //    {200.0f, 450.0f},
   //    {64, 64},
   //    "assets/game/lever.png",
   //    INTERACTABLE
   // );

   // mLeverCount = lever_num;

   //pickup stuff

   // mPickups[0] = new Entity(
   //    {-200.0f, 450.0f},
   //    {40, 40},
   //    "assets/game/health.png",
   //    PICKUP
   // );
   // mPickupTypes[0] = HEALTH;

   // mPickups[1] = new Entity(
   //    {0.0f, 450.0f},
   //    {40, 40},
   //    "assets/game/gem.png",
   //    PICKUP
   // );
   // mPickupTypes[1] = GEM;

   // mPickupCount = 2;

   for (int i = 0; i < mEnemyCount; i++)
   {
      mPickups[mPickupCount] = new Entity(
         mEnemies[i]->getPosition(),
         {40, 40},
         "assets/game/gem.png",
         PICKUP
      );
      mPickupTypes[mPickupCount] = GEM;
      mPickups[mPickupCount]->deactivate();
      mPickupCount++;
   }

   mDialogueActive = true;
   mDialogueIndex  = 0;

}
   

void LevelD::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   if (mDialogueActive)
   {
      if (IsKeyPressed(KEY_SPACE))
      {
         mDialogueIndex++;
         PlaySound(dialogue);
         if (mDialogueIndex >= mDialogueCount) {
            mDialogueActive = false;
            mDialogueCompleted = true;
         }
      }
      return; 
   }

   mGameState.player->update(
      deltaTime,      // delta time / fixed timestep
      nullptr,        // player
      mGameState.collisionMap, // map
      mEnemies,        // collidable entities
      mEnemyCount,              // col. entity count
      mBreakables, // obstacle entities
      mBreakableCount,
      nullptr
   );

   for (int i = 0; i < mEnemyCount; i++)
   {
      Entity *enemy = mEnemies[i];
      if (!enemy->isActive()) continue;

      enemy->update(
         deltaTime,
         mGameState.player,
         mGameState.collisionMap,
         nullptr, 0,
         nullptr, 0,
         nullptr
      );
      if (enemy->isActive() &&
         enemy->getAIType() == RANGED &&
         enemy->getFireTimer() <= 0.0f)
      {
         Vector2 enemyPos = enemy->getPosition();
         Vector2 playerPos = mGameState.player->getPosition();

         Vector2 diff = {
            playerPos.x - enemyPos.x,
            playerPos.y - enemyPos.y
         };

         for (int i = 0; i < GameState::MAX_PROJECTILES; i++)
         {
            if (!mGameState.projectiles[i]->isActive())
            {
               Entity *proj = mGameState.projectiles[i];
               proj->setPosition(enemyPos);
               proj->activate();

               if (fabsf(diff.x) >= fabsf(diff.y))
               {
                  float dir = (diff.x > 0) ? 1.0f : -1.0f;
                  proj->setMovement({ dir, 0.0f });
                  proj->setAngle(dir > 0 ? 0.0f : 180.0f);
                  proj->setColliderDimensions({ 40.0f, 15.0f });
               }
               else
               {
                  float dir = (diff.y > 0) ? 1.0f : -1.0f;
                  proj->setMovement({ 0.0f, dir });
                  proj->setAngle(dir > 0 ? 90.0f : -90.0f);
                  proj->setColliderDimensions({ 15.0f, 40.0f });
               }

               proj->setSpeed(150);
               enemy->resetFireTimer();
               break;
            }
         }
      }
   }

   if (mGameState.player->getWin()) 
      {PlaySound(mGameState.winSound); 
      mGameState.nextSceneID = 5;}

   if (IsKeyPressed(KEY_F)) mGameState.playerDie = true;


   if (mDialogueCompleted == true) {

      if (IsKeyPressed(KEY_L) && mSwordTimer <= 0.0f) {
         mSwordTimer = SWORD_DURATION;
         mGameState.sword->setColliderDimensions({ 64.0f, 40.0f });
         mGameState.sword->setSwing(true);
         mGameState.sword->setAngle(-90);
         mGameState.sword->setSwingDirection(R);
      }

      if (IsKeyPressed(KEY_K) && mSwordTimer <= 0.0f) {
         mSwordTimer = SWORD_DURATION;
         mGameState.sword->setColliderDimensions({ 40.0f, 64.0f });
         mGameState.sword->setSwing(true);
         mGameState.sword->setAngle(0);
         mGameState.sword->setSwingDirection(D);
      }

      if (IsKeyPressed(KEY_J) && mSwordTimer <= 0.0f) {
         mSwordTimer = SWORD_DURATION;
         mGameState.sword->setColliderDimensions({ 64.0f, 40.0f });
         mGameState.sword->setSwing(true);
         mGameState.sword->setAngle(90);
         mGameState.sword->setSwingDirection(L);
      }

      if (IsKeyPressed(KEY_I) && mSwordTimer <= 0.0f) {
         mSwordTimer = SWORD_DURATION;
         mGameState.sword->setColliderDimensions({ 40.0f, 64.0f });
         mGameState.sword->setSwing(true);
         mGameState.sword->setAngle(180);
         mGameState.sword->setSwingDirection(U);
      }
   }
   

   if (mSwordTimer > 0.0f) {
      mSwordTimer -= deltaTime;

      Vector2 playerPos = mGameState.player->getPosition();
      Vector2 swordPos = playerPos;

      switch (mGameState.sword->getSwingDirection()) {
         case R:
               swordPos = { playerPos.x + 52.0f, playerPos.y };
               break;
         case L:
               swordPos = { playerPos.x - 52.0f, playerPos.y };
               break;
         case D:
               swordPos = { playerPos.x, playerPos.y + 58.0f };
               break;
         case U:
               swordPos = { playerPos.x, playerPos.y - 52.0f };
               break;
         default:
               break;
      }

      mGameState.sword->setPosition(swordPos);

      if (mSwordTimer <= 0.0f) {
         mGameState.sword->setSwing(false);
         mGameState.sword->setSwingDirection(NOT);
         mGameState.sword->setColliderDimensions({ 40.0f, 64.0f });
      }
   }

   if (mGameState.sword->isSwinging())
   {
      for (int i = 0; i < mEnemyCount; i++)
      {
         Entity *enemy = mEnemies[i];
         if (!enemy->isActive() || enemy->isEnemyInvincible()) continue;

         if (mGameState.sword->isCollidingWith(enemy))
         {
            enemy->setEnemyHP(enemy->getEnemyHP() - 1);
            enemy->triggerEnemyInvincibility();
            PlaySound(swordHit);

            if (enemy->getEnemyHP() <= 0) {
               enemy->deactivate();
               PlaySound(enemyDie);
               StopMusicStream(mGameState.bgm);
            }
         }
      }

      for (int i = 0; i < mEnemyCount; i++)
      {
         if (mEnemies[i] == nullptr) continue;

         if (!mEnemies[i]->isActive() && 
            mPickups[i] != nullptr   && 
            !mPickupCollected[i]     &&
            !mPickups[i]->isActive())
         {
            mPickups[i]->setPosition(mEnemies[i]->getPosition());
            mPickups[i]->activate();
         }
      }

      for (int i = 0; i < mBreakableCount; i++)
      {
         Entity *obstacle = mBreakables[i];
         if (!obstacle->isActive()) continue;

         if (mGameState.sword->isCollidingWith(obstacle))
         {
            obstacle->deactivate();
         }
      }

   }

   for (int i = 0; i < GameState::MAX_PROJECTILES; i++)
   {
      Entity *proj = mGameState.projectiles[i];
      if (!proj->isActive()) continue;

      Vector2 pos = proj->getPosition();
      Vector2 mov = proj->getMovement();
      pos.x += mov.x * proj->getSpeed() * deltaTime;
      pos.y += mov.y * proj->getSpeed() * deltaTime;
      proj->setPosition(pos);

      if (pos.x < -500 || pos.x > 2000 || pos.y < -500 || pos.y > 2000)
      {
         proj->deactivate();
         continue;
      }

      if (proj->isCollidingWith(mGameState.player) &&
         !mGameState.player->isInvincible())
      {
         mGameState.player->setDamage(true);
         proj->deactivate();
      }
   }


   if (!mDialogueActive && 
      mGameState.sign->isCollidingWith(mGameState.player) &&
      IsKeyPressed(KEY_E))
   {
      mDialogueActive = true;
      mDialogueIndex  = 0;
   }

   //DOOR
   if (!mDialogueActive && 
      mGameState.door->isCollidingWith(mGameState.player) &&
      IsKeyPressed(KEY_E))
   {
      mGameState.nextSceneID = 5;
   }

   //LEVER CODE:

   for (int i = 0; i < mLeverCount; i++)
   {
      if (mLeverPulled[i]) continue;

      if (mLevers[i]->isCollidingWith(mGameState.player) &&
         IsKeyPressed(KEY_E))
      {
         mLeverPulled[i] = true;
         levers_pulled++;

         mLevers[i]->setTexture("assets/game/leverpulled.png");

         if (levers_pulled >= lever_num)
         {
               //LEVER EVENT HERE
               mGameState.nextSceneID = 5;
         }
      }
   }

   for (int i = 0; i < mPickupCount; i++)
   {
      if (mPickupCollected[i]) continue;
      if (!mPickups[i]->isActive()) continue;

      if (mPickups[i]->isCollidingWith(mGameState.player))
      {
         mPickupCollected[i] = true;
         mPickups[i]->deactivate();

         switch (mPickupTypes[i])
         {
               case HEALTH:
                  if (*mGameState.playerHP < 5)
                     *mGameState.playerHP += 1;
                  break;

               case KEY:
                  // UPDATE SOMETHING TO CHANGE
                  mGameState.nextSceneID = 5;
                  break;

               case GEM:
                  // BOSS PICKUP?
                  mGameState.nextSceneID = 5;
                  break;
         }
      }
   }

   if (mGameState.player->isDamaged() && !mGameState.player->isInvincible()) {
      *mGameState.playerHP -= 1;
      mGameState.player->triggerInvincibility();
      PlaySound(playerHurt);

      if (*mGameState.playerHP <= 0)
         mGameState.playerDie = true;
   }

}

void LevelD::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.visualMap->render();

   mGameState.door->render();
   

   if (mGameState.sword->isSwinging()) {
      mGameState.sword->render();
   }
   mGameState.sign->render();

   for (int i = 0; i < GameState::MAX_PROJECTILES; i++)
      if (mGameState.projectiles[i]->isActive())
         mGameState.projectiles[i]->render();

   if (!mDialogueActive &&
      mGameState.sign->isCollidingWith(mGameState.player))
   {
      Vector2 signPos = mGameState.sign->getPosition();
      DrawText(
            "[E]",
            (int)(signPos.x - 15),  
            (int)(signPos.y - 70),  
            24, WHITE
      );
   }

   if (mGameState.door->isCollidingWith(mGameState.player))
   {
      Vector2 doorPos = mGameState.door->getPosition();
      DrawText(
            "[E]",
            (int)(doorPos.x - 15),  
            (int)(doorPos.y - 70),  
            24, WHITE
      );
   }
   
   for (int i = 0; i < mLeverCount; i++)
   {
      mLevers[i]->render();

      if (!mLeverPulled[i] &&
         mLevers[i]->isCollidingWith(mGameState.player))
      {
         Vector2 pos = mLevers[i]->getPosition();
         DrawText("[E]", (int)(pos.x - 15), (int)(pos.y - 70), 24, WHITE);
      }
   }

   for (int i = 0; i < mPickupCount; i++)
    if (mPickups[i] != nullptr && mPickups[i]->isActive())
        mPickups[i]->render();

   for (int i = 0; i < mEnemyCount; i++)
      if (mEnemies[i] != nullptr && mEnemies[i]->isActive())
         mEnemies[i]->render();

   for (int i = 0; i < mBreakableCount; i++)
      if (mBreakables[i] != nullptr && mBreakables[i]->isActive())
         mBreakables[i]->render();


   mGameState.player->render();


}

void LevelD::shutdown()
{
   delete mGameState.player;
   delete mGameState.collisionMap;
   delete mGameState.visualMap;
   delete mGameState.enemy;
   delete mGameState.win;
   delete mGameState.sword;
   delete mGameState.door;

   for (int i = 0; i < mLeverCount; i++)
    delete mLevers[i];

   for (int i = 0; i < mEnemyCount; i++)
    delete mEnemies[i];

   for (int i = 0; i < mPickupCount; i++)
    delete mPickups[i];

   for (int i = 0; i < mBreakableCount; i++)
    delete mBreakables[i];

   UnloadMusicStream(mGameState.bgm);
   UnloadSound(mGameState.jumpSound);
   UnloadSound(mGameState.winSound);
   UnloadSound(mGameState.dieSound);

   UnloadSound(swordHit);
   UnloadSound(dialogue);
   UnloadSound(enemyDie);
   UnloadSound(playerHurt);
}