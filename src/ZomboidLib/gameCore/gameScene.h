#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include <vector>

#include "../core/texCache.h"
#include "gameObject.h"

class GameScene
{
public:
    int uid;
    int scope;
    std::vector<GameObject*> startUpObjects;

    virtual void onLoad(std::vector<TexCache>* requiredTex, std::vector<GameObject*> * startupObjects, int* scope) {}
    virtual void onEnter(bool* loadScope) {}
    virtual void onExit(bool* removeAllObjects, bool* unloadScope) {}

    //viewPort
    //back...
    //
};

#endif // GAMESCENE_H_INCLUDED
