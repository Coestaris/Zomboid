#include "updater.h"

std::vector<GameObject*> Updater::objects;
std::map<int, std::vector<GameObject*>> Updater::events;

milliseconds Updater::tickStartTime;

#ifdef CALCULATE_FPS
double Updater::FPS;
milliseconds Updater::delayCounter;
int Updater::framesCounter;
milliseconds mili_fps_av = milliseconds((int)(1000.0 * FPS_AV_SEC));
#endif // CALCULATE_FPS

bool Updater::Running;
milliseconds mili_fps = milliseconds((int)(1000.0 / FPS_TO_LOCK));
milliseconds mili_zero = milliseconds(0);

milliseconds Updater::getCurrentTime()
{
    return duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
}

void Updater::raiseEvent(EventType eventType, void* data)
{
    if(Updater::events.count((int)eventType) > 0)
    {
        for(GameObject* obj : Updater::events[(int)eventType])
        {
            obj->eventHandler({ eventType, data });
        }
    }
}

void Updater::tick()
{
    raiseEvent(EventType::Update, nullptr);

    glClearColor(0.4, 0.4, 0.4, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

        glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 0.1);
                glVertex3f(-0.7, 0.7, 0);

                glColor3f(0, 0, 1);
                glVertex3f(0.7, 0.7, 0);

                glColor3f(1, 1, 0.0);
                glVertex3f(0, -1, 0);
        glEnd();
    glFlush();
}

void Updater::tickBegin()
{
    Updater::tickStartTime = Updater::getCurrentTime();
}

void Updater::tickEnd()
{
    milliseconds now = Updater::getCurrentTime();
    milliseconds delta = mili_fps - (now - Updater::tickStartTime);
    if(delta > mili_zero) {
        std::this_thread::sleep_for(delta);
    }

    #ifdef CALCULATE_FPS
    Updater::framesCounter += 1;
    Updater::delayCounter += delta;

    if(Updater::delayCounter >= mili_fps_av) {

        Updater::FPS = 1000.0 * (double)Updater::framesCounter / (double)Updater::delayCounter.count();
        std::cout << "FPS:" << Updater::FPS << "\n";

        Updater::framesCounter = 0;
        Updater::delayCounter = mili_zero;

    }
    #endif //CALCULATE_FPS
}

void Updater::init()
{
    Updater::events = std::map<int, std::vector<GameObject*>>();
    Updater::objects = std::vector<GameObject*>();
    Updater::Running = true;
}

void Updater::registerInstance(GameObject* object)
{
    Updater::objects.push_back(object);
}

void Updater::subscribeEvent(EventType eventType, GameObject* object)
{
    if(Updater::events.count((int)eventType) > 0)
    {
        events[(int)eventType].push_back(object);
    } else
    {
        events.insert(std::pair<int,std::vector<GameObject*>>(
            (int)eventType,
            std::vector<GameObject*>()
        ));
        events[(int)eventType].push_back(object);
    }
}

void Updater::redraw()
{
    for (GameObject* object : Updater::objects) {
        object->draw();
    }
}
