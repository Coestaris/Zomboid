#ifndef TEXCACHE_H_INCLUDED
#define TEXCACHE_H_INCLUDED

#include <string>

#include "texture2d.h"

class TexCache
{
public:

    std::string path;
    int identifier;
    int scope;
    Texture2D* tex;
    bool loadTex;

    TexCache(std::string path, bool load, int identifier, int scope) {
        this->path = path;
        this->loadTex = load;
        this->identifier = identifier;
        this->scope = scope;
    }

    TexCache(std::string path, int id, int scope, Texture2D* tex, bool loadTex)
    {
        this->path = path;
        this->identifier = id;
        this->scope = scope;
        this->tex = tex;
        this->loadTex = loadTex;
    }
};

#endif // TEXCACHE_H_INCLUDED
