#include "graphics.h"

void Graphics::initGraphics(std::string title, Vector2i winSize, Vector2i winPos)
{
    const char* c_title = title.c_str();

    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winSize.x, winSize.x);
    glutInitWindowPosition(winPos.x, winPos.y);
    glutCreateWindow(c_title);

    //delete[] c_title;
}

void Graphics::initEvents()
{
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(Graphics::eventKeyUp);
    glutSpecialFunc(Graphics::eventPressedKey);
    glutMotionFunc(Graphics::eventMouseMove);
    glutMouseFunc(Graphics::eventMouseClick);
    glutEntryFunc(Graphics::eventMouseEntry);
    glutKeyboardFunc(Graphics::eventPressedCharKey);
    glutKeyboardUpFunc(Graphics::eventKeyCharUp);

    glutIdleFunc(Graphics::loop);
    glutDisplayFunc(Graphics::loop);
}

#include "../game/player.h"

void Graphics::init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title)
{
    Player* player = new Player();
    Updater::registerInstance((GameObject*)player);
    player->onLoad();

    glutInit(&argc, argv);
    Graphics::initGraphics(title, winSize, winPos);
    Graphics::initEvents();

    glutMainLoop();
}

void Graphics::eventPressedKey(int key, int x, int y)
{

    KeyEventData* ked = new KeyEventData();

    ked->key = key;
    ked->charKey = NULL_CHARKEY;
    ked->x = x;
    ked->y = y;

    Updater::raiseEvent(EventType::KeyPressed, (void*)ked);

    delete ked;
}

void Graphics::eventPressedCharKey(unsigned char key, int x, int y)
{


    KeyEventData* ked = new KeyEventData();
    ked->key = NULL_KEY;
    ked->charKey = key;
    ked->x = x;
    ked->y = y;

    Updater::raiseEvent(EventType::KeyPressed, (void*)ked);

    delete ked;
}

void Graphics::eventKeyCharUp(unsigned char key, int x, int y)
{


    KeyEventData* ked = new KeyEventData();
    ked->key = NULL_KEY;
    ked->charKey = key;
    ked->x = x;
    ked->y = y;

    Updater::raiseEvent(EventType::KeyUp, (void*)ked);

    delete ked;
}

void Graphics::eventKeyUp(int key, int x, int y)
{
    KeyEventData* ked = new KeyEventData();
    ked->key = key;
    ked->charKey = NULL_CHARKEY;
    ked->x = x;
    ked->y = y;

    Updater::raiseEvent(EventType::KeyUp, (void*)ked);

    delete ked;
}

void Graphics::eventMouseClick(int button, int state, int x, int y)
{
    std::cout << "Moved!";
}

void Graphics::eventMouseMove(int x, int y)
{

}

void Graphics::eventMouseEntry(int state)
{

}

void Graphics::loop()
{
    Updater::tickBegin();

    Updater::tick();
    Updater::redraw();

    Updater::tickEnd();
}
