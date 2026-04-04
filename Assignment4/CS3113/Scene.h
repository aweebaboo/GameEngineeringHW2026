#include "Entity.h"

#ifndef SCENE_H
#define SCENE_H

struct GameState
{
    Entity *player = nullptr;
    Entity *win = nullptr;
    Map *map = nullptr;
    Entity *enemy = nullptr;

    Music bgm;
    Sound jumpSound;
    Sound winSound;
    Sound dieSound;

    bool playerDie = false;

    int nextSceneID;


};

class Scene 
{
protected:
    GameState mGameState;
    Vector2 mOrigin;
    const char *mBGColourHexCode = "#000000";
    
public:
    Scene();
    Scene(Vector2 origin, const char *bgHexCode);

    virtual void initialise() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;

    virtual void restart() {return;}
    
    GameState   getState()           const { return mGameState; }
    Vector2     getOrigin()          const { return mOrigin;    }
    const char* getBGColourHexCode() const { return mBGColourHexCode; }

    bool getDie() const { return mGameState.playerDie; }
};

#endif