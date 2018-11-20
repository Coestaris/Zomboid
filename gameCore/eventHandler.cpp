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

void reshape(int _width, int _height) {
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
    glutReshapeFunc(reshape);

    glutEntryFunc(EventHandler::eventMouseEntry);
    glutKeyboardFunc(EventHandler::eventCharKeyDown);
    glutKeyboardUpFunc(EventHandler::eventKeyCharUp);

    glutIdleFunc(EventHandler::loop);
    glutDisplayFunc(EventHandler::loop);
}

void EventHandler::runGame()
{
    glutMainLoop();
}

#include "../game/player.h"
#include "resourceLoader.h"
#include "renderer.h"

Texture2D* tex;

void EventHandler::init(int argc, char **argv, Vector2i winSize, Vector2i winPos, std::string title)
{
    Player* player = new Player();
    Updater::registerInstance((GameObject*)player);
    player->onLoad();
    glutInit(&argc, argv);
    EventHandler::initGraphics(title, winSize, winPos);
    EventHandler::initEvents();

    tex = ResourceLoader::loadTexture("input.png");
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

    glClearColor(0.4, 0.4, 0.4, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    //Updater::tick();
    //Updater::redraw();
    //DrawImage();
    //glClearColor(0, 0, 0, 0);
    //glClear(0);

    Renderer::DrawTexture(tex, Vector2f(0, 0), angle += 0.1, 2);

    Renderer::DrawTexture(tex, Vector2f(sin(angle) * 100, 100), angle / 2, 1);
    glFlush();

    Updater::tickEnd();
}
