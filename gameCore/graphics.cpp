#include "graphics.h"

void Graphics::init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title)
{
    const char* c_title = title.c_str();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winSize.x, winSize.x);
    glutInitWindowPosition(winPos.x, winPos.y);
    glutCreateWindow(c_title);
    glutDisplayFunc(Graphics::loop);
    glutMainLoop();

    delete[] c_title;
}

void Graphics::loop()
{
//    Player p();


    while(Updater::Running) {

        Updater::tickBegin();

        Updater::tick();
        Updater::redraw();

        Updater::tickEnd();
    }
}
