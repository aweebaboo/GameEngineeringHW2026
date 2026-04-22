#include "Scene.h"

#ifndef LEVELA_H
#define LEVELA_H

constexpr int LEVELA_WIDTH = 20,
              LEVELA_HEIGHT = 14;

class LevelA : public Scene {
private:
    unsigned int mVisualData[LEVELA_WIDTH * LEVELA_HEIGHT] = {
        93, 51, 52, 50, 51, 52, 50, 51, 52, 50, 51, 52, 50, 51, 52, 50, 51, 52, 50, 93,
        93, 67, 68, 66, 67, 68, 66, 67, 68, 66, 67, 68, 66, 67, 68, 66, 67, 68, 66, 93,
        79, 83, 84, 82, 83, 84, 82, 83, 84, 82, 83, 84, 82, 83, 84, 82, 83, 84, 82, 80,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        94, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  92,
        95, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 96,
    };

    unsigned int mCollisionData[LEVELA_WIDTH * LEVELA_HEIGHT] = {
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
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
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    };

public:
    static constexpr float TILE_DIMENSION       = 64.0f,
                        ACCELERATION_OF_GRAVITY = 981.0f,
                        END_GAME_THRESHOLD      = 800.0f;

    LevelA();
    LevelA(Vector2 origin, const char *bgHexCode);
    ~LevelA();

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

    bool mDialogueCompleted = false;

    bool getDialogueActive() const override { return mDialogueActive; }

    const DialogueLine* getCurrentDialogueLine() const override {
        if (mDialogueActive && mDialogueIndex < mDialogueCount)
            return &mDialogueLines[mDialogueIndex];
        return nullptr;
    }   

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

    static constexpr int MAX_ENEMIES = 6;
    Entity *mEnemies[MAX_ENEMIES] = { nullptr };
    int mEnemyCount = 0;

    static constexpr int MAX_BREAKABLES = 8;
    Entity *mBreakables[MAX_BREAKABLES] = { nullptr };
    int mBreakableCount = 0;

    Vector2 getCameraLimits() const override {
        return {128.0f, 128.0f};
    }

    Sound swordHit;
    Sound dialogue;

};

#endif