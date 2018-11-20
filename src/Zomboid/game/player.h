#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "objectInclude.h"

class Player : public GameObject
{
public:

    Player() {}

    void onLoad() override {
        std::cout << "Player Inited\n";
        Updater::subscribeEvent(EventType::MouseMove, this);
    }

    void eventHandler(GameEvent event) override {
        if(event.eventType == EventType::MouseMove) {

            MouseEventData* med = (MouseEventData*)event.eventData;
            std::cout << "X: " << med->x << ", Y: " << med->y << "\n";

        }
    }
};

#endif // PLAYER_H_INCLUDED
