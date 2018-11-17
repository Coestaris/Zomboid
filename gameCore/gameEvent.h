#ifndef GAMEVENENT_H_INCLUDED
#define GAMEVENENT_H_INCLUDED

enum class EventType : int {
    Update = 0,
};

typedef struct {
    int eventType;
    void* eventData;

} GameEvent;

#endif // GAMEVENENT_H_INCLUDED
