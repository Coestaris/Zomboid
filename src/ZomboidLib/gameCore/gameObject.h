#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <vector>

#include "../core/vector.h"

#include "gameEvent.h"

typedef long ouid_t;

class GameObject
{

protected:
    virtual void onLoad() {}
    virtual void onCreate() {}

public:
    ouid_t ouid;

    void destroyInstance();

    virtual void eventHandler(GameEvent event) {}
    virtual void draw() {}
};

#endif // GAMEOBJECT_H_INCLUDED
