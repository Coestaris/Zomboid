#include "renderer.h"

void Renderer::DrawTexture(Texture2D* tex, Vector2f position, double angle, double scaleFactor)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex->textureId);

    glTranslatef(0, 0, 0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);
        glVertex2i(position.x, position.y);
        glTexCoord2i(0, 1);
        glVertex2i(position.x + tex->width * scaleFactor, position.y);
        glTexCoord2i(1, 1);
        glVertex2i(position.x, position.y + tex->height * scaleFactor);
        glTexCoord2i(1, 0);
        glVertex2i(position.x + tex->width * scaleFactor, position.y + tex->height * scaleFactor);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
