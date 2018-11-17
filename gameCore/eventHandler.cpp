#include "eventHandler.h"

void EventHandler::initGraphics(std::string title, Vector2i winSize, Vector2i winPos)
{
    const char* c_title = title.c_str();

    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winSize.x, winSize.x);
    glutInitWindowPosition(winPos.x, winPos.y);
    glutCreateWindow(c_title);

    //delete[] c_title;
}

void EventHandler::initEvents()
{
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(EventHandler::eventKeyUp);
    glutSpecialFunc(EventHandler::eventKeyDown);
    glutMotionFunc(EventHandler::eventMouseMove);
    glutPassiveMotionFunc(EventHandler::eventMouseMove);
    glutMouseFunc(EventHandler::eventMouseClick);

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
    //match projection to window resolution (could be in reshape callback)
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, glutGet(GLUT_SCREEN_WIDTH), 0, glutGet(GLUT_SCREEN_HEIGHT), -1, 1);
    glMatrixMode(GL_MODELVIEW);

}


void DrawImage(void) {

    //clear and draw quad with texture (could be in display callback)
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex->textureId);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(100, 100);
        glTexCoord2i(0, 1); glVertex2i(100, 500);
        glTexCoord2i(1, 1); glVertex2i(500, 500);
        glTexCoord2i(1, 0); glVertex2i(500, 100);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFlush(); //don't need this with GLUT_DOUBLE and glutSwapBuffers
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

void EventHandler::loop()
{
    Updater::tickBegin();

    //Updater::tick();
    //Updater::redraw();
    DrawImage();

    Updater::tickEnd();
}
