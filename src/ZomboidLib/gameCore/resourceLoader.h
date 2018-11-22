#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <stdio.h>
#include <SOIL/SOIL.h>
#include <string>
#include <stdexcept>
#include <vector>

#include "../core/utils.h"
#include "../core/texture2d.h"
#include "../core/texCache.h"

#include "gameScene.h"

class ResourceLoader
{

private:
    static std::vector<TexCache> texCache;
    static std::vector<GameScene*> scenes;

    static Texture2D* loadTexture(std::string path);
    static bool GetImageSize(const char *fn, int *x,int *y);

public:
    static void init();

    static bool hasCached(int identifier);

    static void freeTexure(Texture2D* tex);

    static Texture2D* GetTexure(int identifier);
    static void CacheTexures(std::vector<TexCache> data);

    static void ClearCacheByScope(int scope);
    static void ClearCacheById(int identifier);
    static void ClearCache(std::vector<int> identifiers);

    static void loadScope(int scope);
    static void unloadScope(int scope);

    static void pushScene(GameScene* scene);
    static GameScene* getScene(int identifier);
};


#endif // RESOURCELOADER_H_INCLUDED
