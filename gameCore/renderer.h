#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "../core/texture2d.h"
#include "../core/vector.h"

class Renderer
{
public:
    static void DrawTexture(Texture2D* tex, Vector2f position, double angle, double scaleFactor = 1);
};

#endif // RENDERER_H_INCLUDED
