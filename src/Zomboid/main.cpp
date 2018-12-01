#include "main.h"

#define SCENE_ID_MAIN 1

int main(int argc, char **argv)
{
    Updater::init();
    EventHandler::init(argc, argv, Vector2i(500, 500), Vector2i(100, 100), "Game title");

    GameScene* mainS = new MainScene( SCENE_ID_MAIN );
    //ResourceLoader::pushScene(NULL);

    for(unsigned int  i = 0; i < ResourceLoader::scenes.size(); i++) {
        if(ResourceLoader::scenes[i]->uid == mainS->uid) {
            throw std::invalid_argument("Same scene has already loaded");
        }
    }

    //ResourceLoader::scenes.push_back(mainS);


    EventHandler::runGame( SCENE_ID_MAIN );

    //delete[] main;
}
