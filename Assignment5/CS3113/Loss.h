#include "LevelD.h"

#ifndef LOSS_H
#define LOSS_H

class Loss : public Scene {
private:
    

public:
    static constexpr float TILE_DIMENSION       = 75.0f,
                        ACCELERATION_OF_GRAVITY = 981.0f,
                        END_GAME_THRESHOLD      = 800.0f;

    Loss();
    Loss(Vector2 origin, const char *bgHexCode);
    ~Loss();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif