#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "objectInclude.h"

class Player : public GameObject
{
public:

    Player() {}

    void onLoad() override {
        std::cout << "Player Inited\n";
        Updater::subscribeEvent(EventType::Update, this);
        Updater::subscribeEvent(EventType::KeyUp, this);
        Updater::subscribeEvent(EventType::KeyPressed, this);
    }

    void eventHandler(GameEvent event) override {
        if(event.eventType == EventType::Update) {
            std::cout << "\n";
        } else

        if(event.eventType == EventType::KeyUp || event.eventType == EventType::KeyPressed) {

            KeyEventData* ked = (KeyEventData*)event.eventData;
            if(ked->charKey != NULL_CHARKEY) {
                std::cout << "Pressed key is: " << ked->charKey << "\n";
            } else {
                std::cout << "Pressed key is special symbol\n";
            }
        }
    }
};

#endif // PLAYER_H_INCLUDED
