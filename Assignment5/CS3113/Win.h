#include "Menu.h"

#ifndef WIN_H
#define WIN_H

class Win : public Scene {
private:
    

public:
    static constexpr float TILE_DIMENSION       = 75.0f,
                        ACCELERATION_OF_GRAVITY = 981.0f,
                        END_GAME_THRESHOLD      = 800.0f;

    Win();
    Win(Vector2 origin, const char *bgHexCode);
    ~Win();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif