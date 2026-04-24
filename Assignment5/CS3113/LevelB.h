#include "LevelA.h"

#ifndef LEVELB_H
#define LEVELB_H

constexpr int LEVELB_WIDTH = 20,
              LEVELB_HEIGHT = 28;

class LevelB : public Scene {
private:
    unsigned int mVisualData[LEVELB_WIDTH * LEVELB_HEIGHT] = {
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 121, 282, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 241, 203,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 281, 123,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1, 201, 242, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1, 161, 162, 162, 163,   1,   1,   1,   1,   1,   1,   1,   1,
    };

    unsigned int mCollisionData[LEVELB_WIDTH * LEVELB_HEIGHT] = {
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    };

public:
    static constexpr float TILE_DIMENSION       = 64.0f,
                        ACCELERATION_OF_GRAVITY = 981.0f,
                        END_GAME_THRESHOLD      = 800.0f;

    LevelB();
    LevelB(Vector2 origin, const char *bgHexCode);
    ~LevelB();

    void restart();

    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;


    // Sword stuff
    float mSwordTimer = 0.0f;
    static constexpr float SWORD_DURATION = 0.7f;

    // Dialogue stuff
    static constexpr int MAX_DIALOGUE_LINES = 10;
    DialogueLine mDialogueLines[MAX_DIALOGUE_LINES];
    int mDialogueCount    = 0;
    int mDialogueIndex    = 0;
    bool mDialogueActive  = false;

    bool mDialogueCompleted = true;

    bool getDialogueActive() const override { return mDialogueActive; }

    const DialogueLine* getCurrentDialogueLine() const override {
        if (mDialogueActive && mDialogueIndex < mDialogueCount)
            return &mDialogueLines[mDialogueIndex];
        return nullptr;
    }   

    int lever_num    = 2;
    int levers_pulled = 0;

    static constexpr int MAX_LEVERS = 10;
    Entity *mLevers[MAX_LEVERS]       = { nullptr };
    bool    mLeverPulled[MAX_LEVERS]  = { false   };
    int     mLeverCount               = 0;

    static constexpr int MAX_PICKUPS = 10;
    Entity *mPickups[MAX_PICKUPS]       = { nullptr };
    
    enum PickupType { HEALTH, KEY, GEM };
    int mPickupCount = 0;
    PickupType mPickupTypes[MAX_PICKUPS];
    bool mPickupCollected[MAX_PICKUPS] = { false };

    static constexpr int MAX_ENEMIES = 8;
    Entity *mEnemies[MAX_ENEMIES] = { nullptr };
    int mEnemyCount = 0;

    int enemiesKilled = 0;

    static constexpr int MAX_BREAKABLES = 8;
    Entity *mBreakables[MAX_BREAKABLES] = { nullptr };
    int mBreakableCount = 0;

    Vector2 getCameraLimits() const override {
        return {64.0f, 522.0f};
    }

    Sound swordHit;
    Sound playerHurt;
    Sound enemyDie;
    Sound dialogue;

};

#endif