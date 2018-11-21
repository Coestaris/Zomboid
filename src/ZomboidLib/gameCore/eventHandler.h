#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <string>
#include <malloc.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "../core/vector.h"
#include "resourceLoader.h"
#include "updater.h"

class EventHandler
{
private:
    static void loop();
    static void eventKeyDown(int key, int x, int y);
    static void eventCharKeyDown(unsigned char key, int x, int y);
    static void eventKeyCharUp(unsigned char key, int x, int y);
    static void eventKeyUp(int key, int x, int y);
    static void eventMouseClick(int button, int state, int x, int y);
    static void eventMouseMove(int x, int y);
    static void eventMouseEntry(int state);


    static void initGraphics(std::string title, Vector2i winSize, Vector2i winPos);
    static void initEvents();

public:
    static void init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title);
    static void runGame();
};


#endif // GRAPHICS_H_INCLUDED
