#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <string>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "../core/vector.h"
#include "updater.h"

class Graphics
{
private:
    static void loop();

public:
    static void init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title);
};


#endif // GRAPHICS_H_INCLUDED
