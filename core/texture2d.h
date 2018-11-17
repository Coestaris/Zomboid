#ifndef TEXTURE2D_H_INCLUDED
#define TEXTURE2D_H_INCLUDED

#include "GL/freeglut.h"

class Texture2D
{
public:
	Texture2D(GLuint id, int width, int height)
    {
           textureId = id;
           width = width;
           height = height;
    }

	~Texture2D(void)
    {

         glDeleteTextures(1, ((GLuint*)&textureId));
    }

	GLuint textureId;
	int width;
    int height;
};

#endif // TEXTURE2D_H_INCLUDED
