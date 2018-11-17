#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>

#include "../gameCore/gameObject.h"
#include "../gameCore/updater.h"
#include "../gameCore/gameEvent.h"

class Player : public GameObject
{
    Player() {}

    void onLoad() {
        Updater::subscibeEvent((int)EventType::Update, this);
    }

    void eventHandler(GameEvent event) {
        if(event.eventType == (int)EventType::Update) {
            std::cout << "Player Updated\n";
        }
    }
};

#endif // PLAYER_H_INCLUDED
