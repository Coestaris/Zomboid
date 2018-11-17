#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <SOIL/SOIL.h>
#include "../core/texture2d.h"

#include <stdio.h>

class ResourceLoader
{

private:
    static bool GetImageSize(const char *fn, int *x,int *y);

public:
    static Texture2D* loadTexture(const char * path);
};


#endif // RESOURCELOADER_H_INCLUDED
