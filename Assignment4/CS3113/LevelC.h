#include "LevelB.h"

#ifndef LEVELC_H
#define LEVELC_H

class LevelC : public Scene {
private:
    unsigned int mLevelData[LEVEL_WIDTH * LEVEL_HEIGHT] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  27, 0,  0,  0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 0,  0,  27, 0,  0,  27, 0,  0,
        0,  0,  0,  0,  0,  27, 0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        71, 42, 42, 42, 42, 42, 72, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        28, 3,  3,  3,  3,  3,  26, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        28, 3,  3,  3,  3,  3,  26, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

public:
    static constexpr float TILE_DIMENSION       = 75.0f,
                        ACCELERATION_OF_GRAVITY = 981.0f,
                        END_GAME_THRESHOLD      = 800.0f;

    LevelC();
    LevelC(Vector2 origin, const char *bgHexCode);
    ~LevelC();
    
    void restart();

    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif