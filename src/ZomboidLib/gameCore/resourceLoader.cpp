#include "resourceLoader.h"

std::vector<TexCache> ResourceLoader::texCache;


bool ResourceLoader::GetImageSize(const char *fn, int *x,int *y)
{
    FILE *f = fopen(fn,"rb");

    if (f == 0) {
        throw std::invalid_argument("unable to open file");
    };

    fseek(f,0,SEEK_END);

    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (len < 24)
    {
        fclose(f);
        return false;
    }

    unsigned char buf[24];
    fread(buf, 1, 24, f);

    if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F')
    {
        long pos = 2;
        while (buf[2] == 0xFF)
        {
            if (buf[3] == 0xC0 || buf[3] == 0xC1 || buf[3] == 0xC2 || buf[3] == 0xC3 || buf[3] == 0xC9 || buf[3] == 0xCA || buf[3] == 0xCB) break;
            pos += 2 + (buf[4] << 8) + buf[5];
            if (pos + 12 > len) break;
            fseek(f, pos, SEEK_SET);
            fread(buf + 2, 1, 12, f);
        }
    }
    fclose(f);

    // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
    if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
    {
        *y = (buf[7]<<8) + buf[8];
        *x = (buf[9]<<8) + buf[10];
        return true;
    }

    // GIF: first three bytes say "GIF", next three give version number. Then dimensions
    if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
    {
        *x = buf[6] + (buf[7]<<8);
        *y = buf[8] + (buf[9]<<8);
        return true;
    }

    // PNG: the first frame is by definition an IHDR frame, which gives dimensions
    if (
        buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' &&
        buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A &&
        buf[6]==0x1A && buf[7]==0x0A && buf[12]=='I' &&
        buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
    {
        *x = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
        *y = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);

        return true;
    }

    return false;
}

Texture2D * ResourceLoader::loadTexture(std::string path){

    if(!Utils::fileExists(path)) {
        throw std::invalid_argument(path + " file not exist");
    }

    int w, h;
    if(!ResourceLoader::GetImageSize(path.c_str(), &w, &h)) {
        //puts("Unable to get image size");
        w = -1;
        h = -1;
    }

	GLuint id = SOIL_load_OGL_texture
	(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	printf("Loaded texture \"%s\". W: %i, H: %i OGlID: %li\n",
        path.c_str(), w, h, id);

	return new Texture2D(id, w, h);
}

void ResourceLoader::freeTexure(Texture2D* tex) {
    tex->destroy();
    delete tex;
}

void ResourceLoader::init()
{
    ResourceLoader::texCache = std::vector<TexCache> ();
}

Texture2D* ResourceLoader::GetTexure(int identifier)
{
    for(int i = 0; i < ResourceLoader::texCache.size(); i++) {
        if(ResourceLoader::texCache[i].identifier == identifier) {
            return ResourceLoader::texCache[i].tex;
        }
    }

    throw std::invalid_argument("Unable to find specified texture");
}

bool ResourceLoader::hasCached(int identifier)
{
    for(int i = 0; i < ResourceLoader::texCache.size(); i++) {
        if(ResourceLoader::texCache[i].identifier == identifier) {
            return true;
        }
    }

    return false;
}

void ResourceLoader::CacheTexures(std::vector<TexCache> data)
{
    for(TexCache tc : data) {
        if(!ResourceLoader::hasCached(tc.identifier)) {
            ResourceLoader::texCache.push_back(
                {
                    tc.path,
                    tc.identifier,
                    tc.scope,
                    ResourceLoader::loadTexture(tc.path)
                }
            );
        }
    }
}

void ResourceLoader::ClearCacheByScope(int scope)
{
    for(int i = ResourceLoader::texCache.size(); i >= 0 ; i--) {
        if(ResourceLoader::texCache[i].scope == scope) {
            ResourceLoader::texCache.erase(
                ResourceLoader::texCache.begin() + i
            );
        }
    }
}

void ResourceLoader::ClearCacheById(int identifier)
{
    for(int i = ResourceLoader::texCache.size(); i >= 0 ; i--) {
        if(ResourceLoader::texCache[i].identifier == identifier) {
            ResourceLoader::texCache.erase(
                ResourceLoader::texCache.begin() + i
            );
            return;
        }
    }
}

void ResourceLoader::ClearCache(std::vector<int> identifiers)
{
//TODO!
}


