#include "Entity.h"

#ifndef SCENE_H
#define SCENE_H

struct GameState
{
    Entity *player = nullptr;
    Entity *win = nullptr;
    Entity *enemy = nullptr;
    Entity *sword = nullptr;
    Entity *sign = nullptr;
    Entity *door = nullptr;

    Map *collisionMap = nullptr;
    Map *visualMap = nullptr;

    Music bgm;
    Sound jumpSound;
    Sound winSound;
    Sound dieSound;

    bool playerDie = false;

    int nextSceneID;

    int *playerHP = nullptr;

    static constexpr int MAX_PROJECTILES = 100;
    Entity *projectiles[MAX_PROJECTILES] = { nullptr };

};

struct DialogueLine {
    const char* speaker;
    const char* text;
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


    virtual Vector2 getCameraLimits() const {
        return {128.0f, 128.0f};
    }
    
    GameState   getState()           const { return mGameState; }
    Vector2     getOrigin()          const { return mOrigin;    }
    const char* getBGColourHexCode() const { return mBGColourHexCode; }

    bool getDie() const { return mGameState.playerDie; }

    void setplayerHP(int *hp) { mGameState.playerHP = hp; }

    virtual bool                getDialogueActive()      const { return false;   }
    virtual const DialogueLine* getCurrentDialogueLine() const { return nullptr; }
};

#endif