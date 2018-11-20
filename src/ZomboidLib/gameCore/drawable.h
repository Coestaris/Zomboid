#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include "../core/texture2d.h"
#include "../core/vector.h"

class DrawableObject : public GameObject
{

public:
    Texture2D tex;
    double angle;
    Vector2f position;
};

#endif // DRAWABLE_H_INCLUDED
