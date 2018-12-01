#include "eventHandler.h"

void EventHandler::initGraphics(std::string title, Vector2i winSize, Vector2i winPos)
{
    const char* c_title = title.c_str();

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winSize.x, winSize.x);
    glutInitWindowPosition(winPos.x, winPos.y);
    glutCreateWindow(c_title);

    //delete[] c_title;

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, glutGet(GLUT_SCREEN_WIDTH), 0, glutGet(GLUT_SCREEN_HEIGHT), -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void EventHandler::ReshapeFunc(int _width, int _height) {
    glViewport(0, 0, _width, _height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _width, 0, _height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void EventHandler::initEvents()
{
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(EventHandler::eventKeyUp);
    glutSpecialFunc(EventHandler::eventKeyDown);
    glutMotionFunc(EventHandler::eventMouseMove);
    glutPassiveMotionFunc(EventHandler::eventMouseMove);
    glutMouseFunc(EventHandler::eventMouseClick);
    glutReshapeFunc(EventHandler::ReshapeFunc);

    glutEntryFunc(EventHandler::eventMouseEntry);
    glutKeyboardFunc(EventHandler::eventCharKeyDown);
    glutKeyboardUpFunc(EventHandler::eventKeyCharUp);

    glutIdleFunc(EventHandler::loop);
    glutDisplayFunc(EventHandler::loop);
}

void EventHandler::runGame(int sceneIndex)
{
    Updater::loadScene(sceneIndex);
    glutMainLoop();
}

void EventHandler::init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title)
{
    glutInit(&argc, argv);
    ResourceLoader::init();
    EventHandler::initGraphics(title, winSize, winPos);
    EventHandler::initEvents();
}

void EventHandler::eventKeyDown(int key, int x, int y)
{
    KeyEventData* ked = new KeyEventData();
    ked->key = key;
    ked->charKey = NULL_CHARKEY;
    ked->x = x;
    ked->y = y;
    Updater::raiseEvent(EventType::KeyDown, (void*)ked);
    delete ked;
}

void EventHandler::eventCharKeyDown(unsigned char key, int x, int y)
{
    KeyEventData* ked = new KeyEventData();
    ked->key = NULL_KEY;
    ked->charKey = key;
    ked->x = x;
    ked->y = y;
    Updater::raiseEvent(EventType::KeyDown, (void*)ked);
    delete ked;
}

void EventHandler::eventKeyCharUp(unsigned char key, int x, int y)
{
    KeyEventData* ked = new KeyEventData();
    ked->key = NULL_KEY;
    ked->charKey = key;
    ked->x = x;
    ked->y = y;
    Updater::raiseEvent(EventType::KeyUp, (void*)ked);
    delete ked;
}

void EventHandler::eventKeyUp(int key, int x, int y)
{
    KeyEventData* ked = new KeyEventData();
    ked->key = key;
    ked->charKey = NULL_CHARKEY;
    ked->x = x;
    ked->y = y;
    Updater::raiseEvent(EventType::KeyUp, (void*)ked);
    delete ked;
}

void EventHandler::eventMouseClick(int button, int state, int x, int y)
{
    MouseEventData* med = new MouseEventData();
    med->button = button;
    med->state = state;
    med->x = x;
    med->y = y;
    Updater::raiseEvent(EventType::MouseClick, (void*)med);
    delete med;
}

void EventHandler::eventMouseMove(int x, int y)
{
    MouseEventData* med = new MouseEventData();
    med->button = NULL_BUTTON;
    med->state = NULL_STATE;
    med->x = x;
    med->y = y;
    Updater::raiseEvent(EventType::MouseMove, (void*)med);
    delete med;
}

void EventHandler::eventMouseEntry(int state)
{
    MouseEventData* med = new MouseEventData();
    med->button = NULL_BUTTON;
    med->state = state;
    med->x = NULL_COORD;
    med->y = NULL_COORD;
    Updater::raiseEvent(EventType::MouseEntry, (void*)med);
    delete med;
}

float angle = 0;
#include <math.h>

void EventHandler::loop()
{
    Updater::tickBegin();

    Updater::tick();
    Updater::redraw();

    glFlush();
    Updater::tickEnd();
}
