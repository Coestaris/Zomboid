#include "renderer.h"

inline Vector2f Renderer::createPoint(Vector2f pos, double cos, double sin, double hw, double hh, int s1, int s2) {
    return Vector2f(
        pos.x + s1*hw*cos - s2*hh*sin,
        pos.y + s1*hw*sin + s2*hh*cos
    );
}


void Renderer::DrawTexture(Texture2D* tex, Vector2f position, double angle, double scaleFactor)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->textureId);

    glPushMatrix();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    double hw= tex->width / 2;
    double hh= tex->height / 2;

	double acos = cos(angle) * scaleFactor;
    double asin = sin(angle) * scaleFactor;

    Vector2f p1 = Renderer::createPoint(position, acos, asin, hw, hh, -1, -1);
    Vector2f p2 = Renderer::createPoint(position, acos, asin, hw, hh, -1,  1);
    Vector2f p3 = Renderer::createPoint(position, acos, asin, hw, hh,  1, -1);
    Vector2f p4 = Renderer::createPoint(position, acos, asin, hw, hh,  1,  1);

    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(0, 1); glVertex2f(p1.x, p1.y);
        glTexCoord2f(0, 0); glVertex2f(p2.x, p2.y);
        glTexCoord2f(1, 1); glVertex2f(p3.x, p3.y);
        glTexCoord2f(1, 0); glVertex2f(p4.x, p4.y);
    }
    glEnd();

    glPopMatrix();
}

void Renderer::ClearScreen()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::FlushScreen()
{
    glFlush();
}
