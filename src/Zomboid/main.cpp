#include "main.h"

#define SCENE_ID_MAIN 1

int main(int argc, char **argv)
{
    Updater::init();
    EventHandler::init(argc, argv, Vector2i(500, 500), Vector2i(100, 100), "Game title");

    ResourceLoader::pushScene(new MainScene( SCENE_ID_MAIN ));

    EventHandler::runGame( SCENE_ID_MAIN );
}
