#ifndef UPDATER_H_INCLUDED
#define UPDATER_H_INCLUDED

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <map>

#include "gameScene.h"
#include "gameObject.h"
#include "renderer.h"

#define CALCULATE_FPS
#define FPS_TO_LOCK 60

#ifdef CALCULATE_FPS
    #define FPS_AV_SEC 0.5
#endif // CALCULATE_FPS

using namespace std::chrono;

class Updater
{
private:
    static std::vector<GameObject*> objects;
    static std::map<int, std::vector<GameObject*>> events;

    static milliseconds tickStartTime;
    static milliseconds getCurrentTime();

    #ifdef CALCULATE_FPS
    static int framesCounter;
    static milliseconds delayCounter;
    #endif // CALCULATE_FPS

    static GameScene* currentScene;

public:
    static void raiseEvent(EventType eventType, void* data);

    static void init();

    static void tick();
    static void tickBegin();
    static void tickEnd();

    static void redraw();

    static void subscribeEvent(EventType eventType, GameObject* object);

    static void registerInstance(GameObject* object);
    static void destroyInstance(ouid_t ouid);

    static bool Running;

    static void loadScene(int scene);

    #ifdef CALCULATE_FPS
    static double FPS;
    #endif // CALCULATE_FPS
};

#endif // UPDATER_H_INCLUDED
