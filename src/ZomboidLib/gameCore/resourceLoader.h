#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <stdio.h>
#include <SOIL/SOIL.h>
#include <string>
#include <stdexcept>
#include <vector>

#include "../core/utils.h"
#include "../core/texture2d.h"

typedef struct {
    std::string path;
    int identifier;
    int scope;
    Texture2D* tex;

} TexCache;

class ResourceLoader
{

private:
    static std::vector<TexCache> texCache;

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
};


#endif // RESOURCELOADER_H_INCLUDED
