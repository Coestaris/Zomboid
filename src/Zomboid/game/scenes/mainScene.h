#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include "../../../ZomboidLib/gameCore/objectInclude.h"
#include "../player.h"

#define GAME_IMGID_INPUT 1
#define GAME_IMGSCOPE_MAIN 0

class MainScene : public GameScene
{
public:

    MainScene(int id) {
        uid = id;
    }

    void onLoad(std::vector<TexCache>* requiredTex, std::vector<GameObject*> * startupObjects, int* scope) override {
        *scope = GAME_IMGSCOPE_MAIN;

        requiredTex->push_back( TexCache("input.png", false, GAME_IMGID_INPUT, GAME_IMGSCOPE_MAIN) );

        startupObjects->push_back( new Player() );
    }

    void onEnter(bool* loadScope) override {
        *loadScope = true;
    }

    void onExit(bool* deleteAll, bool* unloadScope) override {
        *deleteAll = true;
        *unloadScope = true;
    }
};

#endif // MAIN_H_INCLUDED
