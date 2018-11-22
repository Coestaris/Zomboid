#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "../core/texture2d.h"
#include "../core/vector.h"

#include <math.h>

class Renderer
{
private:
    static inline Vector2f createPoint(Vector2f pos, double cos, double sin, double hw, double hh, int s1, int s2);

public:
    static void DrawTexture(Texture2D* tex, Vector2f position, double angle, double scaleFactor = 1);
    static void ClearScreen();
    static void FlushScreen();
};

#endif // RENDERER_H_INCLUDED
