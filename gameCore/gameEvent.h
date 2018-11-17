#ifndef GAMEVENENT_H_INCLUDED
#define GAMEVENENT_H_INCLUDED

#include "GL/freeglut.h"

#define NULL_CHARKEY '\0'
#define NULL_KEY -1

enum class EventType : int {
    Update = 0,

    KeyPressed = 1,
    KeyUp = 2,
    MouseClick = 3,
    MouseMove = 4,
    MouseEntry = 5
};

typedef struct {
    unsigned char charKey;
    int key;
    int x;
    int y;

} KeyEventData;

typedef struct {
    int button;
    int state;
    int x;
    int y;

} MouseEventData;

typedef struct {
    EventType eventType;
    void* eventData;

} GameEvent;

#endif // GAMEVENENT_H_INCLUDED
